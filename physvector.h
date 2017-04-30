#ifndef _PHYSVECTOR_H
#define _PHYSVECTOR_H

#include <cmath> // for sqrt function

class PhysVector
{
  public:
    PhysVector() : x_(0), y_(0), z_(0) {}
    PhysVector(double x) : x_(x), y_(0), z_(0) {}
    PhysVector(double x, double y) : x_(x), y_(y), z_(0) {}
    PhysVector(double x, double y, double z) : x_(x), y_(y), z_(z) {}
    PhysVector(const PhysVector &p) : x_(p.x_), y_(p.y_), z_(p.z_) {}
    ~PhysVector() {}
    bool operator == (const PhysVector& p)
    {
      return (x_ == p.x_ && y_ == p.y_ && z_ == p.z_);
    }
    bool operator != (const PhysVector& p)
    {
      return !(*this == p);
    }
    PhysVector& operator = (const PhysVector& p)
    {
      if (this != &p)
      {
        x_ = p.x_;
        y_ = p.y_;
        z_ = p.z_;
      }
      return *this;
    }
    PhysVector operator + (const PhysVector& p)
    {
      PhysVector sum;
      sum.x_ = this->x_ + p.x_;
      sum.y_ = this->y_ + p.y_;
      sum.z_ = this->z_ + p.z_;
      return sum;
    }
    PhysVector& operator += (const PhysVector& p)
    {
      this->x_ = this->x_ + p.x_;
      this->y_ = this->y_ + p.y_;
      this->z_ = this->z_ + p.z_;
      return *this;
    }
    PhysVector operator - (const PhysVector& p)
    {
      PhysVector difference;
      difference.x_ = this->x_ - p.x_;
      difference.y_ = this->y_ - p.y_;
      difference.z_ = this->z_ - p.z_;
      return difference;
    }
    PhysVector operator * (const PhysVector& p)
    {
      PhysVector product;
      product.x_ = this->x_ * p.x_;
      product.y_ = this->y_ * p.y_;
      product.z_ = this->z_ * p.z_;
      return product;
    }
    PhysVector operator * (const double& c)
    {
      PhysVector product;
      product.x_ = this->x_ * c;
      product.y_ = this->y_ * c;
      product.z_ = this->z_ * c;
      return product;
    }
    PhysVector operator / (const PhysVector& p)
    {
      PhysVector quotient;
      quotient.x_ = this->x_ / p.x_;
      quotient.y_ = this->y_ / p.y_;
      quotient.z_ = this->z_ / p.z_;
      return quotient;
    }
    PhysVector operator / (const double& d)
    {
      PhysVector quotient;
      quotient.x_ = this->x_ / d;
      quotient.y_ = this->y_ / d;
      quotient.z_ = this->z_ / d;
      return quotient;
    }
    double GetX() { return x_;}
    double GetY() { return y_;}
    double GetZ() { return z_;}
    void SetX(double x) { x_ = x; }
    void SetY(double y) { y_ = y; }
    void SetZ(double z) { z_ = z; }
    double GetLength() { return sqrt(x_*x_ + y_*y_ + z_*z_); }
    double DotProduct(const PhysVector &a, const PhysVector &b)
    {
      return a.x_ * b.x_ + a.y_ * b.y_ + a.z_ * b.z_;
    }
    PhysVector& CrossProduct(const PhysVector &a, const PhysVector &b)
    {
      PhysVector * p = new PhysVector();
      p->SetX((a.y_ * b.z_) - (b.y_ * a.z_));
      p->SetY((a.z_ * b.x_) - (b.z_ * a.x_));
      p->SetZ((a.x_ * b.y_) - (b.x_ * a.y_));
      return *p;
    }
  private:
    double x_, y_, z_;
};

#endif
