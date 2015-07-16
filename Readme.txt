--------------------------------------
---------- Coding Standards ----------
--------------------------------------


---------------- C++ -----------------

-- Language Version --

All code shall conform to the C++11 standard.  Taking full advantage of all of the features C++11 and the STL has to offer is encouraged, but with consideration to predictable memory use, code performance, and toolchain support.

-- Indentation --

Tabs shall be used to indent code to the extent dictated by the current block, with spaces used after that for readability.  This allows each coder

Example:

void foo(int param1, int param2
*********int param3, int param4)
{
  ->  if ( someLongConditional == someLongFunctionName() &&
  ->  *****anotherLongConditional == anotherLongFunctionName() )
  ->  {
  ->    ->  bar(someLongParam,
  ->    ->  ****anotherParam);
  ->  }
}