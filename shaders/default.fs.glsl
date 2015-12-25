#version 330 core

in vec3 vPosition;
in vec3 vNormal;
in vec2 vTexCoords;

out vec3 fColor;

uniform sampler2D uTexture;

uniform vec3 uKd;
uniform vec3 uKs;
uniform float uShininess;


#define MAX_LIGHTS 10
uniform int uNbLights;
uniform struct Light {
   vec4 coord;
   vec3 intensity;
} uLights[MAX_LIGHTS];


/*#define MAX_LIGHTS 10

struct Light {
   vec4 coord;
   vec3 intensity;
};

uniform int uNbLights;
uniform struct uLights {
	Light lights[MAX_LIGHTS];
};*/


vec3 blinnPhong() {

	vec3 fragmentColor = vec3(0);

	vec3 diffuse = texture(uTexture, vTexCoords).rgb * uKd;
	vec3 vNormalNorm = normalize(vNormal);
	vec3 w_zero = normalize( -vPosition );


	for ( int i = 0; i < uNbLights; ++i ) {

		vec3 w_i = vec3( 0.0, 0.0, 0.0 );
		vec3 L_i = vec3( 0.0, 0.0, 0.0 );

		if ( uLights[i].coord.w == 1.0 ) {

			w_i = normalize( uLights[i].coord.xyz - vPosition );
			float d = distance(uLights[i].coord.xyz, vPosition);
			L_i = uLights[i].intensity / (d * d);

		} else {

			w_i = normalize( -uLights[i].coord.xyz );
			L_i = uLights[i].intensity;

		}

		vec3 halfVector = (w_zero + w_i) / 2;

	    fragmentColor += L_i * ( diffuse * ( dot(w_i, vNormalNorm ) ) + uKs * ( pow( dot(halfVector, vNormalNorm), uShininess ) ) );

	}

	return fragmentColor;

	/*vec3 diffuse = texture(uTexture, vTexCoords).rgb * uKd;

	vec3 vNormalNorm = normalize(vNormal);

	vec3 w_zero = normalize( -vPosition );

	vec3 w_i = vec3( 0.0, 0.0, 0.0 );
	vec3 L_i = vec3( 0.0, 0.0, 0.0 );

	if ( uLightCoord.w == 1.0 ) {

		w_i = normalize( uLightCoord.xyz - vPosition );
		float d = distance(uLightCoord.xyz, vPosition);
		L_i = uLightIntensity / (d * d);

	} else {

		w_i = normalize( -uLightCoord.xyz );
		L_i = uLightIntensity;

	}

	vec3 halfVector = (w_zero + w_i) / 2;

	return L_i * ( diffuse * ( dot(w_i, vNormalNorm ) ) + uKs * ( pow( dot(halfVector, vNormalNorm), uShininess ) ) );*/
}


void main() {

	fColor = blinnPhong();

}
