#include <algorithm>
#include <array>
#include <execution>
#include <iostream>
#include <shared_mutex>
#include <sstream>

void checkThread() {
  static auto threads = std::vector<std::thread::id>{};
  static auto threadMutex = std::shared_mutex{};
  auto const threadId = std::this_thread::get_id();
  auto const thisIsANewThread = [&] {
    auto readLock = std::shared_lock{threadMutex};
    auto const it = std::find(threads.begin(), threads.end(), threadId);
    return it == threads.end();
  }();
  if (thisIsANewThread) {
    auto const writeLock = std::lock_guard{threadMutex};
    auto oss = std::ostringstream{};
    oss << "Thread count: [" << threads.size() << "]. Most recent: ["
        << threadId << "]. Other threads [";
    auto separator = std::string{};
    std::for_each(threads.begin(), threads.end(),
                  [&separator, &oss](std::thread::id const& id) {
                    oss << separator << id;
                    separator = ", ";
                  });
    oss << "].\n";
    std::cout << oss.str();
    threads.emplace_back(threadId);
  }
}

// Simple data structure
template <typename T, int Width, int Height>
class Image_ final {
 public:
  using TData = std::array<T, Width * Height>;
  auto begin() { return data->begin(); }
  auto end() { return data->end(); }
  auto begin() const { return data->begin(); }
  auto end() const { return data->end(); }

 private:
  std::shared_ptr<TData> data = std::make_shared<TData>();
};

// Relevant structures
using Image1uc = Image_<unsigned char, 4096, 2048>;
using Image1d = Image_<double, 4096, 2048>;

int main() {
  // Assume images contains valuable data
  auto const images = std::vector<Image1uc>(1000);

  // We want to calculate some double value per image
  auto calculatedValues = std::vector<double>(images.size());
  // Our computation is completely independent between each image.
  std::transform(
      std::execution::par_unseq, images.begin(), images.end(),
      calculatedValues.begin(), [](Image1uc const& image) {
        // Here we check if this is a new thread or an old one.
        checkThread();
        // First we compute an intermediate representation of the image. This
        // representation is memory intensive.
        auto intermediateImages = [&image] {
          auto intermediateImage = Image1d{};
          std::transform(std::execution::par_unseq, image.begin(), image.end(),
                         intermediateImage.begin(),
                         [](unsigned char const pixelVal) {
                           return std::pow(pixelVal / 256., 2.);
                         });
          // Assume several more such intermediate images are generated with
          // different calculations
          return std::array{intermediateImage, intermediateImage,
                            intermediateImage, std::move(intermediateImage)};
        }();
        // Now we use these intermediate images to calculate a metric per image
        return std::transform_reduce(
            std::execution::par_unseq, intermediateImages.begin(),
            intermediateImages.end(), 0., std::plus<double>{},
            [](Image1d const& image) {
              return std::reduce(
                  std::execution::par_unseq, image.begin(), image.end(), 0.,
                  [](double const val, double const sum) { return val + sum; });
            });
      });
  return 0;
}