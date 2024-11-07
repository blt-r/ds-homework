project(
  'data-structures',
  'cpp',
  default_options : [
    'b_sanitize=address,undefined',
    'cpp_std=c++20'
  ]
)

rational_number = executable('rational-number-tests', '1-RationalNumber/main.cpp')
test('rational-number', rational_number)

vector = executable('vector-tests', '2-Vector/main.cpp')
test('vector', vector)

forward_list = executable('forward-list-tests', '3-ForwardList/main.cpp')
test('forward-list', forward_list)

list = executable('list-tests', '4-List/main.cpp')
test('list', list)

