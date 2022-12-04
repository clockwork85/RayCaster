//
// Created by Bray, Matthew D ERDC-RDE-GSL-MS CIV on 11/13/22.
//

#include "RayCaster.h"

std::vector<Intersection> intersect_world(const World& world, const Ray& ray) {
    std::vector<Intersection> totintersections;
    for (const auto& shape: world.objects) {
        std::vector<Intersection> intersections = shape->intersect(ray);
        // Put all intersections into one vector
        for ( const Intersection& intersection : intersections) {
            totintersections.emplace_back(intersection);
        }
    }
    // Sort intersections by t
    std::sort(totintersections.begin(), totintersections.end(), [](const Intersection& a, const Intersection& b) {
        return a.t < b.t;
    });

    return totintersections;
}

Vector4f reflect(const Vector4f& in, const Vector4f& normal) {
    return in - (normal * 2 * in.dot(normal));
}

Intersection hit(std::vector<Intersection> intersections) {
    std::sort(intersections.begin(), intersections.end(), [](const Intersection& a, const Intersection& b) {
        return a.t < b.t;
    });
    for (const Intersection& intersection : intersections) {
        if (intersection.t > 0) {
            return intersection;
        }
    }
    return Intersection();
}

Color lighting(const Material& material,
               const Shape* shape,
               const Light& light,
               const Vector4f& position,
               const Vector4f& eye,
               const Vector4f& normal,
               const float intensity) {
    Color material_color = material.color;
    if(material.pattern != nullptr) {
        material_color = pattern_at_object(material.pattern, shape, position);
    }
    Color effective_color = material_color * light.intensity;
    Color sum = Colors::BLACK;
    // for each sample on the light
    Color ambient = effective_color * material.ambient;
    // Attempt to turn Light into a PointLight and if fails try an AreaLight
    try {
        const PointLight& pointlight = dynamic_cast<const PointLight&>(light);
//        std::cout << "light type: " << pointlight.type << " has " << pointlight.samples << " lights with " << pointlight.positions.size() << " positions." <<  std::endl;
        Vector4f lightv = (pointlight.position - position).normalized();
        float light_dot_normal = lightv.dot(normal);
        if (light_dot_normal < 0 || intensity == 0.0) {
            return ambient;
        }
        Color diffuse = effective_color * material.diffuse * light_dot_normal * intensity;
        Vector4f reflectv = reflect(-lightv, normal);
        float reflect_dot_eye = reflectv.dot(eye);
        if (reflect_dot_eye <= 0) {
            return ambient + diffuse;
        }
        Color specular = light.intensity * material.specular * pow(reflect_dot_eye, material.shininess);
        return ambient + diffuse + specular;
    } catch (std::bad_cast& e) {
        try {
            AreaLight& arealight = dynamic_cast<AreaLight&>(const_cast<Light&>(light));
            arealight.create_positions();
//            std::cout << "LIGHT type: " << arealight.type << " has " << arealight.samples << " lights with " << arealight.positions.size() << " positions." <<  std::endl;
            for (int i = 0; i < arealight.positions.size(); i++) {
//                std::cout << "Sample " << i << " is at " << arealight.positions[i] << std::endl;
                Vector4f lightv = (arealight.positions[i] - position).normalized();
                float light_dot_normal = lightv.dot(normal);
                if (light_dot_normal >= 0 && !is_equal(intensity, 0.0)) {
                    // Diffuse
                    Color diffuse = effective_color * material.diffuse * light_dot_normal;
                    sum = sum + diffuse;
                    // Specular
                    Vector4f inverse_lightv = -lightv;
                    Vector4f reflectv = reflect(inverse_lightv, normal);
                    float reflect_dot_eye = reflectv.dot(eye);
                    if (reflect_dot_eye > 0.0) {
                        float factor = pow(reflect_dot_eye, material.shininess);
                        Color specular = light.intensity * material.specular * factor;
                        sum = sum + specular;
                    }
                }
//                std::cout << "Sum after " << i << " samples: " << sum << std::endl;
            }
            return ambient + (sum / static_cast<float>(arealight.positions.size())) * intensity;
        } catch (std::bad_cast& e) {
            std::cerr << "Lighting: Light is not a PointLight or AreaLight" << std::endl;
        }
    }

//
//    for (int i = 0; i < light.samples; i++) {
//        Vector4f lightv;
//        if (light.type == LightType::POINT) {
//            lightv = (light.position - position).normalized();
//        } else if (light.type == LightType::AREA) {
//            lightv = (light.positions[i] - position).normalized();
//        }
//        float light_dot_normal = lightv.dot(normal);
//        if (light_dot_normal < 0) {
//            sum = sum + Colors::BLACK;
//        } else {
//            sum = sum + effective_color * material.diffuse * light_dot_normal;
//            Vector4f reflectv = reflect(-lightv, normal);
//            float reflect_dot_eye = reflectv.dot(eye);
//            if (reflect_dot_eye <= 0) {
//                sum = sum + Colors::BLACK;
//            } else {
//                float factor = pow(reflect_dot_eye, material.shininess);
//                sum = sum + light.intensity * material.specular * factor;
//            }
//        }
//    }

//    Vector4f light_vector = (light.position - position).normalized();
//    const float light_dot_normal = light_vector.dot(normal);
//    Color ambient = effective_color * material.ambient;
//    Color diffuse;
//    Color specular;
//    Color sum = Colors::BLACK;
//    for(int i = 0; i < light.samples; i++) {
//        if (light_dot_normal < 0 || intensity == 0.0) {
//            diffuse = Colors::BLACK;
//            specular = Colors::BLACK;
//        } else {
//            diffuse = effective_color * material.diffuse * light_dot_normal * intensity;
//            Vector4f inv_light_vector = -light_vector;
//            Vector4f reflect_vector = reflect(inv_light_vector, normal);
//            float reflect_dot_eye = reflect_vector.dot(eye);
//            if (reflect_dot_eye <= 0) {
//                specular = Colors::BLACK;
//            } else {
//                float factor = pow(reflect_dot_eye, material.shininess);
//                specular = light.intensity * material.specular * factor * intensity;
//            }
//        }
//    }
//    std::cout << "Ambient: " << ambient << std::endl;
//    std::cout << "Diffuse: " << diffuse << std::endl;
//    std::cout << "Specular: " << specular << std::endl;
//    return ambient + diffuse + specular;
}

bool is_shadowed(const World& world, const Vector4f& light_position, const Vector4f& point) {
    const Vector4f v = light_position - point;
    const float distance = v.norm();
    const Vector4f direction = v.normalized();
    const Ray r = Ray(point, direction);
    const std::vector<Intersection> intersections = intersect_world(world, r);
    const auto h = hit(intersections);
    if (h.object != nullptr && h.t < distance) {
        return true;
    }
    return false;
    // return (h.t > 0) && (h.t < distance);
}

Computation prepare_computations(const Intersection& intersection, const Ray& ray, const std::vector<Intersection>& intersections) {
    Computation comps;
    comps.t = intersection.t;
    comps.point = ray.position(comps.t);
    comps.object = intersection.object;
    comps.eyev = -ray.direction;
    comps.normalv = comps.object->normal_at(comps.point);
    if (comps.normalv.dot(comps.eyev) < 0) {
        comps.inside = true;
        comps.normalv = -comps.normalv;
    } else {
        comps.inside = false;
    }
    comps.reflectv = reflect(ray.direction, comps.normalv);
    comps.over_point = comps.point + comps.normalv * EPSILON;
    comps.under_point = comps.point - comps.normalv * EPSILON;
//    return comps;
    // Refraction of n1 and n2
    std::vector<const Shape*> containers{};
    for (const Intersection& i : intersections) {
        if (i == intersection) {
            if (containers.empty()) {
                comps.n1 = 1.0f;
            } else {
                comps.n1 = containers.back()->material.refractive_index;
            }
        }
        auto it = std::find(containers.begin(), containers.end(), i.object);
        if (it != containers.end()) {
            containers.erase(it);
        } else {
            containers.emplace_back(i.object);
        }
        if (i == intersection) {
            if (containers.empty()) {
                comps.n2 = 1.0f;
            } else {
                comps.n2 = containers.back()->material.refractive_index;
            }
            break;
        }
    }
    return comps;
}

Color shade_hit(const World& world, const Computation& comps, const int remaining) {
    Color color = Colors::BLACK;
    Color surface = Colors::BLACK;
    for (const auto& light : world.lights) {
//        std::cout << "going through lights" << std::endl;
//        std::cout << "Light position: " << light->position << std::endl;
//        std::cout << "Light type: " << light->type << std::endl;
        auto intensity = 0.0f;
        try {
            const auto &point_light = dynamic_cast<const PointLight &>(*light);
//            std::cout << "Light is a PointLight" << std::endl;
            intensity = intensity_at_pointlight(point_light, comps.over_point, world);
        } catch (std::bad_cast& e) {
            try {
                auto &area_light = dynamic_cast<AreaLight &>(*light);
//                std::cout << "Light is an AreaLight" << std::endl;
                intensity = intensity_at_arealight(area_light, comps.over_point, world);
            } catch (std::bad_cast& e) {
                std::cout << "Error: Light type not supported" << std::endl;
            }
        }
        surface =  lighting(comps.object->material, comps.object, *light, comps.over_point, comps.eyev, comps.normalv, intensity);
//        intensity = intensity_at_arealight(*areaLight, comps.over_point, world);
//        std::cout << "Area light positions: " << areaLight->positions.size() << std::endl;
//        surface =  lighting(comps.object->material, comps.object, *areaLight, comps.over_point, comps.eyev, comps.normalv, intensity);
//        const PointLight* point_light = dynamic_cast<PointLight*>(light.get());
//        const float intensity = intensity_at_pointlight(*point_light, comps.over_point, world);

        const Color reflected = reflected_color(world, comps, remaining);
        const Color refracted = refracted_color(world, comps, remaining);

        if(comps.object->material.reflective > 0 && comps.object->material.transparency > 0) {
            const float reflectance = schlick(comps);
            color = color + surface + reflected * reflectance + refracted * (1 - reflectance);
        } else {
            color = color + surface + reflected + refracted;
        }
    }
    return color;
}

Color color_at(const World& world, const Ray& ray, const int remaining) {
    std::vector<Intersection> intersections = intersect_world(world, ray);
    const auto intersection = hit(intersections);
    if(intersection.object == nullptr)  {
        return Colors::BLACK;
    }
    const auto comps = prepare_computations(intersection, ray, intersections);
    return shade_hit(world, comps, remaining);
}

Color reflected_color(const World& world, const Computation& comps, const int remaining) {
    if (remaining <= 0) {
        return Colors::BLACK;
    }
    if (is_equal(comps.object->material.reflective, 0.0f, EPSILON)) {
        return Colors::BLACK;
    }
    Ray reflect_ray {comps.over_point, comps.reflectv};
    Color color = color_at(world, reflect_ray, remaining - 1);
    return color * comps.object->material.reflective;
}

Color refracted_color(const World& world, const Computation& comps, const int remaining) {
    if (remaining <= 0) {
        return Colors::BLACK;
    }
    if (is_equal(comps.object->material.transparency, 0.0f, EPSILON)) {
        return Colors::BLACK;
    }
    const float n_ratio = comps.n1 / comps.n2;
    const float cos_i = comps.eyev.dot(comps.normalv);
    const float sin2_t = n_ratio * n_ratio * (1.0f - cos_i * cos_i);
    if (sin2_t > 1.0f) {
        return Colors::BLACK;
    }
    const float cos_t = sqrt(1.0f - sin2_t);
    const Vector4f direction = comps.normalv * (n_ratio * cos_i - cos_t) - comps.eyev * n_ratio;
    const Ray refract_ray {comps.under_point, direction};
    return color_at(world, refract_ray, remaining - 1) * comps.object->material.transparency;
}

float schlick(const Computation& comps) {
    float cos = comps.eyev.dot(comps.normalv);
    if (comps.n1 > comps.n2) {
        const float n = comps.n1 / comps.n2;
        const float sin2_t = n * n * (1.0f - cos * cos);
        if (sin2_t > 1.0f) {
            return 1.0f;
        }
        const float cos_t = sqrt(1.0f - sin2_t);
        cos = cos_t;
    }
    float r0 = pow((comps.n1 - comps.n2) / (comps.n1 + comps.n2), 2);
    return r0 + (1.0f - r0) * pow((1.0f - cos), 5.0f);
}

Ray ray_for_pixel(const Camera& camera, const int px, const int py) {
    float xoffset = (px + 0.5f) * camera.pixel_size;
    float yoffset = (py + 0.5f) * camera.pixel_size;
    float world_x = camera.half_width - xoffset;
    float world_y = camera.half_height - yoffset;
    Vector4f pixel = camera.transform.inverse() * create_point(world_x, world_y, -1.0f);
    Vector4f origin = camera.transform.inverse() * create_point(0.0f, 0.0f, 0.0f);
    Vector4f direction = (pixel - origin).normalized();
    return Ray(origin, direction);
}

Canvas render(const Camera& camera, const World& world) {
    Canvas image = Canvas(camera.hsize, camera.vsize);

    for (int y = 0; y < camera.vsize; y++) {
        std::cerr << "\rScanlines remaining: " << camera.vsize - y <<  " " << std::flush;
        for (int x = 0; x < camera.hsize; x++) {
            Ray ray = ray_for_pixel(camera, x, y);
            Color color = color_at(world, ray, 4);
            image.write_pixel(x, y, color);
        }
    }
    return image;
}

//  new light factory pattern
//float intensity_at(Light* light, const Vector4f& point, const World& world) {
////    if (const auto areaLight = dynamic_cast<AreaLight*>(light)) {
////        return intensity_at(*areaLight, point, world);
////    }
//    if (const auto pointLight = dynamic_cast<PointLight*>(light)) {
//        return intensity_at_pointlight(*pointLight, point, world);
//    }
//    return 0.0f;
//}

float intensity_at_pointlight(const PointLight& light, const Vector4f& point, const World& world) {
    const bool in_shadow = is_shadowed(world, light.position, point);
    if (in_shadow) {
        return 0.0f;
    }
    return 1.0f;
}


Vector4f point_on_light(AreaLight& light, const float u, const float v) {
    Vector4f pt = light.corner + light.uvec * (u + light.jitter_by()) + light.vvec * (v + light.jitter_by());
    light.positions.push_back(pt);
    return pt;
}

float intensity_at_arealight(AreaLight& light, const Vector4f& point, const World& world) {
    float total_intensity = 0.0f;
    for (int v = 0; v < light.vsteps; v++) {
        for (int u = 0; u < light.usteps; u++) {
            const Vector4f p = point_on_light(light, u, v);
//            std::cout << "u = " << u << " v = " << v << " p = " << p << std::endl;
            // const float intensity = intensity_at_pointlight(light, p, world);
            if(!is_shadowed(world, p, point)) {
                total_intensity += 1.0f;
            }
//            std::cout << "total_intensity = " << total_intensity << std::endl;
            // total_intensity += intensity;
        }
    }
    return total_intensity / static_cast<float>(light.samples);
}

std::ostream& operator<<(std::ostream& os, const LightType& type){
    switch(type) {
        case LightType::POINT:
             os << "POINT";
             break;
        case LightType::AREA:
             os << "AREA";
             break;
    }
    return os;
}