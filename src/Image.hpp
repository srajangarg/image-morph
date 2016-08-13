#ifndef __Image_hpp__
#define __Image_hpp__

#include <string>

/** An image with 1 byte per channel. */
class Image
{
  private:
    int w, h, nc;
    unsigned char * buf;

  public:
    /** Default constructor. */
    Image() : w(0), h(0), nc(0), buf(NULL) {}

    /** Create an empy image of the specified dimensions. */
    Image(int w_, int h_, int nc_);

    /**
     * Load from a file. \a req_nc is the requested number of channels in the loaded image. If it is zero, the number of
     * channels in the disk image will be preserved. Else, the image will be converted to \a req_nc channels.
     */
    Image(std::string const & path, int req_nc = 0);

    /** Copy constructor. */
    Image(Image const & src);

    /** Destructor. */
    ~Image();

    /** Assignment operator. */
    Image & operator=(Image const & src);

    /**
     * Load from a file. \a req_nc is the requested number of channels in the loaded image. If it is zero, the number of
     * channels in the disk image will be preserved. Else, the image will be converted to \a req_nc channels.
     */
    bool load(std::string const & path, int req_nc = 0);

    /** Save to a file. */
    bool save(std::string const & path) const;

    /**
     * Resize the image to a given width, height and number of channels. Existing data will be destroyed unless the dimensions
     * match exactly.
     */
    bool resize(int w_, int h_, int nc_);

    /** Check if this image has dimensions identical to another image. */
    bool hasSameDimsAs(Image const & other) const;

    /** Get the width of the image. */
    int width() const { return w; }

    /** Get the height of the image. */
    int height() const { return h; }

    /** Get the number of channels in the image. */
    int numChannels() const { return nc; }

    /** Get a pointer to the pixel data. */
    unsigned char const * data() const { return buf; }

    /** Get a pointer to the pixel data. */
    unsigned char * data() { return buf; }

    /** Get a pointer to the first byte of a pixel. */
    unsigned char const * pixel(int row, int col) const { return buf + (row * w + col) * nc; }

    /** Get a pointer to the first byte of a pixel. */
    unsigned char * pixel(int row, int col) { return buf + (row * w + col) * nc; }

    /** Get a pointer to the first byte of a row of pixels. */
    unsigned char const * scanline(int row) const { return buf + (row * w) * nc; }

    /** Get a pointer to the first byte of a row of pixels. */
    unsigned char * scanline(int row) { return buf + (row * w) * nc; }

}; // class Image

#endif // __Image_hpp__
