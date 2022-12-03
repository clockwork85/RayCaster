//
// Created by Bray, Matthew D ERDC-RDE-GSL-MS CIV on 11/19/22.
//

#ifndef RAYCASTER_LIGHTS_H
#define RAYCASTER_LIGHTS_H

#include <Eigen/Core>
#include "Color.h"
#include "MathUtils.h"

using Vector4f = Eigen::Vector4f;

struct NumberGenerator {
    virtual float next() = 0;
//    float next() {
//        // Cycle through the values
//        if (index >= values.size()) {
//            index = 0;
//        }
//        return values[index++];
//    }

    int index {0};
    std::vector<float> values;
};

struct CyclicGenerator : NumberGenerator {
    CyclicGenerator(std::initializer_list<float> list) {
        values = std::vector<float>(list);
    }
    float next() override {
        // Cycle through the values
        if (index >= values.size()) {
            index = 0;
        }
        return values[index++];
    }
    int index{0};
    std::vector<float> values;
};

struct RandomGenerator : NumberGenerator {
    RandomGenerator() {
        std::random_device rd;
        gen = std::mt19937(rd());
        dis = std::uniform_real_distribution<float>(0.0, 1.0);
    }
    float next() override {
        return dis(gen);
    }
    std::mt19937 gen;
    std::uniform_real_distribution<float> dis;
};

struct Light {
    virtual ~Light() = default;
    Light() = delete;

    Light(const Vector4f& position, const Color& intensity) : position(position), intensity(intensity) {}

    // Equality
    inline bool operator==(const Light& rhs) const {
        return (position == rhs.position && intensity == rhs.intensity);
    }

    Vector4f position{0, 0, 0, 1};
    Color intensity{1, 1, 1};
};

struct PointLight : public Light {
    PointLight(const Vector4f &position, const Color &intensity) : Light(position, intensity) {}
};

// http://raytracerchallenge.com/bonus/area-light.html
class AreaLight : public Light {
public:
    //AreaLight() : Light(create_point(0.0f, 0.0f, 0.0f), Color(1.0f, 1.0f, 1.0f)) {}
    AreaLight(const Vector4f &corner,
              const Vector4f &full_uvec,
              const unsigned int usteps,
              const Vector4f &full_vvec,
              const unsigned int vsteps,
              const Color &intensity) : Light(create_point(0, 0.9, -2), intensity),
                                        corner(corner),
                                        uvec(full_uvec / static_cast<float>(usteps)),
                                        usteps(usteps),
                                        vvec(full_vvec / static_cast<float>(vsteps)),
                                        vsteps(vsteps),
                                        samples(usteps * vsteps) {}

    const Vector4f corner;
    const Vector4f uvec;
    const unsigned int usteps;
    const Vector4f vvec;
    const unsigned int vsteps;
    const unsigned int samples;
    NumberGenerator *generator = nullptr;

    void set_jitter(NumberGenerator *generator) {
        this->generator = generator;
    }

    float jitter_by() const {
        if (generator == nullptr) {
            return 0.5f;
        }
        return generator->next();
    }
};
#endif //RAYCASTER_LIGHTS_H
