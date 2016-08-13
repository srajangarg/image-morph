#include "Image.hpp"
#include "stb_image.hpp"
#include "stb_image_write.hpp"
#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <iostream>

std::string
toLower(std::string const & s)
{
  std::string result = s;
  std::transform(result.begin(), result.end(), result.begin(), ::tolower);
  return result;
}

Image::Image(int w_, int h_, int nc_)
: w(0), h(0), nc(0), buf(NULL)
{
  resize(w_, h_, nc_);
}

Image::Image(std::string const & path, int req_nc)
{
  if (!load(path, req_nc))
    throw ("Could not load image from " + path).c_str();
}

Image::Image(Image const & src)
: w(0), h(0), nc(0), buf(NULL)
{
  *this = src;
}

Image::~Image()
{
  std::free(buf);
}

Image &
Image::operator=(Image const & src)
{
  resize(src.w, src.h, src.nc);
  std::memcpy(buf, src.buf, (size_t)(w * h * nc));

  return *this;
}

bool
Image::load(std::string const & path, int req_nc)
{
  std::free(buf);
  buf = stbi_load(path.c_str(), &w, &h, &nc, req_nc);

  if (!buf)
  {
    std::cerr << "Could not load image from " << path << std::endl;
    return false;
  }

  if (req_nc != 0)
    nc = req_nc;

  return true;
}

bool
Image::save(std::string const & path) const
{
  if (path.length() >= 4)
  {
    std::string ext = toLower(path.substr(path.length() - 4, 4));
    bool ok = true;
    if (ext == ".png")
    {
      ok = (bool)stbi_write_png(path.c_str(), w, h, nc, buf, w * nc);
      if (ok) return true;
    }
    else if (ext == ".bmp")
    {
      ok = (bool)stbi_write_bmp(path.c_str(), w, h, nc, buf);
      if (ok) return true;
    }

    if (!ok)
    {
      std::cerr << "Error load image: " << path << std::endl;
      return false;
    }
  }

  std::cerr << "Unsupported output image format: " << path << std::endl;
  return false;
}

bool
Image::resize(int w_, int h_, int nc_)
{
  if (w == w_ && h == h_ && nc == nc_)
    return true;

  if (w_ < 0 || h_ < 0 || nc_ < 0)
  {
    std::cerr << "Image dimensions must be non-negative" << std::endl;
    return false;
  }

  std::free(buf);

  size_t num_bytes = (size_t)(w_ * h_ * nc_);
  if (num_bytes > 0)
    buf = (unsigned char *)std::malloc(num_bytes);
  else
    buf = NULL;

  w = w_;
  h = h_;
  nc = nc_;

  return true;
}

bool
Image::hasSameDimsAs(Image const & other) const
{
  return w == other.w && h == other.h && nc == other.nc;
}
