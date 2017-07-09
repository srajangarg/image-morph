#ifndef __LineSegment_hpp__
#define __LineSegment_hpp__

#include "Algebra3.hpp"
#include <cassert>
#include <iostream>

/** A line segment, defined by its start and end point. */
class LineSegment
{
  private:
    Vec2 pts[2];  ///< The start and end points of the segment

  public:
    /** Default constructor. */
    LineSegment() {}

    /** Construct from endpoints. */
    LineSegment(Vec2 const & s, Vec2 const & e)
    {
      pts[0] = s;
      pts[1] = e;
    }

    Vec2 const & start() const { return pts[0]; }  ///< Get the start of the segment.
    Vec2 const & end()   const { return pts[1]; }  ///< Get the end of the segment.

    void setStart(Vec2 const & p) { pts[0] = p; }  ///< Set the start of the segment.
    void setEnd  (Vec2 const & p) { pts[1] = p; }  ///< Set the end of the segment.

    /** Get an endpoint of the segment. */
    Vec2 const & endpoint(int i) const
    {
      assert(i >= 0 && i < 2);
      return pts[i];
    }

    /** Set an endpoint of the segment. */
    void setEndpoint(int i, Vec2 const & p)
    {
      assert(i >= 0 && i < 2);
      pts[i] = p;
    }

    /** Set both endpoints of the segment. */
    void setEndpoints(Vec2 const & p, Vec2 const & q)
    {
      pts[0] = p;
      pts[1] = q;
    }

    /** Get the squared length of the segment. */
    double length2() const { return (pts[1] - pts[0]).length2(); }

    /** Get the length of the segment. */
    double length() const { return std::sqrt(length2()); }

    /** Get the unnormalized direction vector from start() to end(). */
    Vec2 direction() const { return end() - start(); }

    Vec2 perp() const
    {
      return direction().perp();
    }
    /**
     * Get the parametric location of a point when orthogonally projected onto the line containing the segment. In other words,
     * if the point nearest p on the line is start() + u * (end() - start()), get the value of the parameter u.
     */
    double lineParameter(Vec2 const & p) const
    {
      return ((end() - start()) * (p - start()))/length2();
    }

    /** Get the signed distance of a point from the line containing segment. */
    double signedLineDistance(Vec2 const & p) const
    {
      return ((p - start()) * perp())/length();
    }

    /**
     * Get the unsigned distance of a point from the segment, assuming u = pointParameter(p) and v = lineDistance(p) have
     * already been evaluated.
     */
    double segmentDistance(Vec2 const & p, double u, double v) const
    {
      // projects before start()
      if(u < 0)
        return (p - start()).length();
      // projects on the line
      else if (u > 1)
        return (p - start()).length();
      // projects after end()
      else
        return abs(v);
      return 0;
    }

    /** Get the unsigned distance of a point from the segment. */
    double segmentDistance(Vec2 const & p) const
    {
      double u = lineParameter(p);
      double v = signedLineDistance(p);
      return segmentDistance(p, u, v);
    }

    /** Get a new segment by linearly interpolating between the endpoints of two existing segments. */
    LineSegment lerp(LineSegment const & target, double t) const
    {
      return LineSegment((1 - t) * start() + t * target.start(),
                         (1 - t) * end()   + t * target.end());
    }

}; // class LineSegment

/** Read the segment from an output stream. */
inline std::istream &
operator>>(std::istream & in, LineSegment & seg)
{
  Vec2 p, q;
  in >> p >> q;
  seg.setEndpoints(p, q);
  return in;
}

/** Write the segment to an output stream. */
inline std::ostream &
operator<<(std::ostream & out, LineSegment & seg)
{
  out << seg.start() << seg.end();
  return out;
}

#endif // __LineSegment_hpp__
