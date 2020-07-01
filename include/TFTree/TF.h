#pragma once

#include <iostream>

class TF {

public:

    TF() = delete;

    explicit TF(double x, double y, double z) :
        x_{x},
        y_{y},
        z_{z} {
    }

    TF operator*(const TF& rTF) const {
        auto result = TF(x_ + rTF.getX(), y_ + rTF.getY(), z_ + rTF.getZ());
        return result;
    }

    const TF& operator*=(const TF& rTF) {
        x_ += rTF.x_;
        y_ += rTF.y_;
        z_ += rTF.z_;
        return *this;
    }

    TF operator-() const {
        return TF(-x_, -y_, -z_);
    }

    void inverse() {
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

protected:

    double x_;
    double y_;
    double z_;

    friend std::ostream& operator<<(std::ostream& os, const TF& tf);
};

std::ostream& operator<<(std::ostream& os, const TF& tf) {
    os << tf.x_ << ' ' << tf.y_ << ' ' << tf.z_;
    return os;
}