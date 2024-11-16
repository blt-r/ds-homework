project(
  'data-structures',
  'cpp',
  default_options: ['b_sanitize=address,undefined', 'cpp_std=c++20'],
)

inc = include_directories('Common')

rational_number = executable(
  'rational-number-tests',
  '1-RationalNumber/main.cpp',
  include_directories: inc,
)
test('rational-number', rational_number)

vector = executable(
  'vector-tests',
  '2-Vector/main.cpp',
  include_directories: inc,
)
test('vector', vector)

forward_list = executable(
  'forward-list-tests',
  '3-ForwardList/main.cpp',
  include_directories: inc,
)
test('forward-list', forward_list)

list = executable(
  'list-tests',
  '4-List/main.cpp',
  include_directories: inc,
)
test('list', list)

set = executable(
  'set-tests',
  '5-Set/main.cpp',
  '5-Set/Set.cpp',
  include_directories: inc,
)
test('set', set)