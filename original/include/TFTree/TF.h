#pragma once

class TF {

public:

    TF() = delete;

    TF(double x, double y, double z) :
        x_{x},
        y_{y},
        z_{z} {

    }

    TF operator*(const TF& rTF) const {
        return TF(x_ + rTF.getX(), y_ + rTF.getY(), z_ + rTF.getZ());
    }

    TF operator*=(const TF& rTF) const {
        return *this * rTF;
    }

    TF operator-() const {
        return TF(-x_, -y_, -z_);
    }

    TF inverse() {
        x_ = -x_;
        y_ = -y_;
        z_ = -z_;
    }

    TF inverted() const {
        return TF(-x_, -y_, -z_);
    }

    [[nodiscard]] double getX() const {return x_;}
    [[nodiscard]] double getY() const {return y_;}
    [[nodiscard]] double getZ() const {return z_;}

    void setX(double x) {x_ = x;}
    void setY(double y) {y_ = y;}
    void setZ(double z) {z_ = z;}

private:

    double x_;
    double y_;
    double z_;
};