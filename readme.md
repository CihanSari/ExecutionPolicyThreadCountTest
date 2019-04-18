# Execution policy thread counts
## MSVC 2019 x64
### Debug configuration
65 unique thread ids launched. Visual Studio 2019 Diagnostic Tools shows 13gb process memory. Threads from console output:
`Thread count: [64]. Most recent: [50312]. Other threads [52792, 54940, 38844, 54896, 49212, 5532, 39704, 54296, 53408, 45160, 43208, 55660, 53608, 51312, 49772, 52168, 55576, 48500, 12928, 53216, 52924, 55416, 46336, 21820, 45680, 3672, 51900, 14700, 50732, 36748, 52996, 49428, 52336, 51092, 22860, 53720, 49696, 50428, 48100, 56060, 7536, 54168, 49988, 47860, 45508, 55608, 51784, 16952, 52728, 53712, 40568, 37592, 45820, 43080, 54032, 50384, 52880, 55916, 8952, 52324, 24780, 51556, 29420, 51628].`

### Release configuration
19 unique thread ids launched. Visual Studio 2019 Diagnostic Tools shows 10gb process memory. Threads from console output:
`Thread count: [18]. Most recent: [30748]. Other threads [52136, 49504, 24400, 56152, 47364, 52884, 55924, 4860, 55816, 55852, 55120, 54012, 55600, 36636, 38360, 38880, 25376, 54220].`
