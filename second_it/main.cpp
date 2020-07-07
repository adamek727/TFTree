#include <iostream>

#include <rtl/Transformation.h>

int main() {


    auto tf = rtl::RigidTf3D<double>::identity();
    auto tr = rtl::Translation3D<double>::identity();
    auto rot = rtl::Rotation3D<double>::identity();

    auto result = rot(tr(tf));
    int i = 5;

}
