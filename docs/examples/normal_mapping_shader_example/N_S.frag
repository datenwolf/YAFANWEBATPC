/* Copyright (c) 2008, Ciardhubh
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification, are permitted
 * provided that the following conditions are met:
 *
 *  * Redistributions of source code must retain the above copyright notice, this list of conditions
 *    and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright notice, this list of
 *    conditions and the following disclaimer in the documentation and/or other materials provided
 *    with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
 * FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY
 * WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. */

struct lightDataType {
    vec4  ambient; 
    vec4  diffuse; 
    vec4  specular; 
    vec4  position;
};

uniform lightDataType light;

uniform float shininess; // Shininess exponent for specular highlights

uniform sampler2D diffuseTexture;
uniform sampler2D normalMap;
uniform sampler2D specularMap;

varying vec3 tbnDirToLight; // Direction to light in tangent space
varying vec3 tbnHalfVector; // Half vector in tangent space

void main(void) {
    // Base colour from diffuse texture
    vec4 baseColour = texture2D(diffuseTexture, gl_TexCoord[0].xy);

    // Uncompress normal from normal map texture
    vec3 normal = normalize(texture2D(normalMap, gl_TexCoord[0].xy).xyz * 2.0 - 1.0);
    // Depending on the normal map's format, the normal's Y direction may have to be inverted to
    // achieve the correct result. This depends - for example - on how the normal map has been
    // created or how it was loaded by the engine. If the shader output seems wrong, uncomment
    // this line:
    // normal.y = -normal.y;
   
    // Ambient
    vec4 ambient = light.ambient * baseColour;
    
    // Diffuse
    // Normalize interpolated direction to light
    vec3 tbnNormDirToLight = normalize(tbnDirToLight);
    // Full strength if normal points directly at light
    float diffuseIntensity = max(dot(tbnNormDirToLight, normal), 0.0);
    vec4 diffuse = light.diffuse * baseColour * diffuseIntensity;

    // Specular
    vec4 specular = vec4(0.0, 0.0, 0.0, 0.0);
    // Only calculate specular light if light reaches the fragment.
    if (diffuseIntensity > 0.0) {
        // Colour of specular reflection
        vec4 specularColour = texture2D(specularMap, gl_TexCoord[0].xy); 
        // Specular strength, Blinn�Phong shading model
        float specularModifier = max(dot(normal, normalize(tbnHalfVector)), 0.0); 
        specular = light.specular * specularColour * pow(specularModifier, shininess);
    }

    // Sum of all lights
    gl_FragColor = clamp(ambient + diffuse + specular, 0.0, 1.0);
    
    // Prevent blending due to lighting and use the diffuse texture's alpha value.
    gl_FragColor.a = baseColour.a;
}
