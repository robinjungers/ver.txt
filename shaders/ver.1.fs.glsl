#version 330 core

in vec3 vPosition;
in vec3 vNormal;
in vec2 vTexCoords;

out vec4 fColor;


uniform sampler2D uTexture;

uniform vec3 uKd;
uniform vec3 uKs;
uniform float uShininess;
uniform vec2 uViewportDimensions;

#define MAX_LIGHTS 10
uniform int uNbLights;
uniform struct Light {
   vec4 coord;
   vec3 intensity;
} uLights[MAX_LIGHTS];

uniform bool uCastsLight;
uniform bool uIsLine;


vec3 blinnPhong() {

	vec3 fragmentColor = vec3( 0 );

	vec3 diffuse = texture( uTexture, vTexCoords ).rgb * uKd;
	vec3 vNormalNorm = normalize( vNormal );
	vec3 w_zero = normalize( -vPosition );

	for ( int i = 0; i < uNbLights; ++i ) {

		vec3 w_i = vec3( 0.0, 0.0, 0.0 );
		vec3 L_i = vec3( 0.0, 0.0, 0.0 );

		if ( uLights[i].coord.w == 1.0 ) {

			w_i = normalize( uLights[i].coord.xyz - vPosition );
			float d = distance( uLights[i].coord.xyz, vPosition );
			L_i = uLights[i].intensity / (d * d);

		} else {

			w_i = normalize( -uLights[i].coord.xyz );
			L_i = uLights[i].intensity;

		}

		vec3 halfVector = ( w_zero + w_i ) / 2;

	  vec3 tempColor = L_i * ( diffuse * ( dot( w_i, vNormalNorm ) ) + uKs * ( pow( dot( halfVector, vNormalNorm ), uShininess ) ) );

    tempColor.r = clamp( tempColor.r, 0.0, 1.0 );
	  tempColor.g = clamp( tempColor.g, 0.0, 1.0 );
	  tempColor.b = clamp( tempColor.b, 0.0, 1.0 );

	  fragmentColor += tempColor;

	}

	return fragmentColor + 2 * diffuse;
}

float map(float value, float inMin, float inMax, float outMin, float outMax) {

	return outMin + (outMax - outMin) * ((value - inMin) / (inMax - inMin));

}

void main() {

  if ( uIsLine )
		fColor = vec4(1);
	else if ( !uCastsLight )
		fColor = texture(uTexture, vTexCoords);
	else
		fColor = vec4( blinnPhong(), 1 );

  vec2 screenSize = (uViewportDimensions.x == 0) ? vec2( 800.0, 600.0 ) : uViewportDimensions;

  float d = abs(distance( gl_FragCoord.xy, screenSize*0.5 ));
  float dmax = abs(distance( vec2(0.0), screenSize*0.5 ));
  fColor.rgb -= 0.015 * exp( 1 * map( d, 0, dmax, 0, 4 ));

}
