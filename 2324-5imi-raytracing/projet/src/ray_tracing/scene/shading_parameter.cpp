/*
**    TP CPE Lyon
**    Copyright (C) 2015 Damien Rohmer
**
**    This program is free software: you can redistribute it and/or modify
**    it under the terms of the GNU General Public License as published by
**    the Free Software Foundation, either version 3 of the License, or
**    (at your option) any later version.
**
**   This program is distributed in the hope that it will be useful,
**    but WITHOUT ANY WARRANTY; without even the implied warranty of
**    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**    GNU General Public License for more details.
**
**    You should have received a copy of the GNU General Public License
**    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "shading_parameter.hpp"

#include "lib/3d/vec3.hpp"
#include "image/color.hpp"
#include "lib/common/basic_functions.hpp"

#include <cmath>

namespace cpe
{

shading_parameter::shading_parameter(float ambiant_param,
                                     float diffuse_param,
                                     float specular_param,
                                     float specular_exponent_param)
    :ambiant(ambiant_param),
      diffuse(diffuse_param),
      specular(specular_param),
      specular_exponent(specular_exponent_param)
{

}


color compute_shading(shading_parameter const& shading,
                      color const& input,
                      vec3 const& p,
                      vec3 const& p_light,
                      vec3 const& normal,
                      vec3 const& p_camera)
{

    // ********************************************* //
    //  [TO DO] Calcul d'illumination pour un sommet 3D + normal + couleur original
    //
    // ALGORITHME:
    //
    // c0 <- couleur initiale
    // b <- couleur blanche (ou couleur de la lumiere)
    // d <- vecteur unitaire pointant vers la source lumineuse
    // t <- vecteur unitaire pointant vers la camera
    // s <- symétrique de d par rapport à la normale
    //
    // k_ambiant = ambiant
    // k_diffus  = cos(normal,d)_[0,1]
    // k_specular= (cos(s,d)_[0,1])^m
    //
    // c = (c_ambiant + c_diffus)*c0 + c_specular*b
    //
    // ********************************************* //
    color c0 = input;
    color b = {1.0f,1.0f,1.0f};
    vec3 d = normalized(p_light-p);
    vec3 t = normalized(p_camera-p);
    vec3 s = reflected(d,normalized(normal));

    float k_ambiant =shading.ambiant;
    float k_diffus = shading.diffuse;
    float k_specular = shading.specular;

    float I_ambiant = k_ambiant;
    float I_diffus = k_diffus*clamp(dot(d,normal));
    float alpha = shading.specular_exponent;
    float I_specular = k_specular*pow(clamp(dot(s,t)),alpha);
    color c = (I_ambiant + I_diffus)*c0 + I_specular*b;
    return c;
//    return input;

}


}
