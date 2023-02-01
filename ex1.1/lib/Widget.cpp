#include <iostream>
#include <random>

#include <Widget.hpp>

Widget rvref::init(Vector &&vec)
{
  return Widget{std::move(vec)}; // TODO: improve if possible
}

Widget lvref::init(Vector &vec)
{
  return Widget{vec}; // TODO: improve if possible
}

Widget value::init(Vector vec)
{
  return Widget{std::move(vec)}; // TODO: improve if possible
}