#version 330 core

in vec3 vPosition;
in vec3 vNormal;
in vec2 vTexCoords;

out vec4 fColor;


uniform sampler2D uTexture;

uniform vec3 uKd;
uniform vec3 uKs;
uniform float uShininess;
uniform float uViewportDimensions;

#define MAX_LIGHTS 10
uniform int uNbLights;
uniform struct Light {
   vec4 coord;
   vec3 intensity;
} uLights[MAX_LIGHTS];

uniform bool uCastsLight;
uniform bool uIsLine;



vec3 mod289(vec3 x) {
  return x - floor(x * (1.0 / 289.0)) * 289.0;
}

vec4 mod289(vec4 x) {
  return x - floor(x * (1.0 / 289.0)) * 289.0;
}

vec4 permute(vec4 x) {
     return mod289(((x*34.0)+1.0)*x);
}

vec4 taylorInvSqrt(vec4 r) {
  return 1.79284291400159 - 0.85373472095314 * r;
}

float snoise(vec3 v) {

  const vec2  C = vec2(1.0/6.0, 1.0/3.0) ;
  const vec4  D = vec4(0.0, 0.5, 1.0, 2.0);

  // First corner
  vec3 i  = floor(v + dot(v, C.yyy) );
  vec3 x0 =   v - i + dot(i, C.xxx) ;

  // Other corners
  vec3 g = step(x0.yzx, x0.xyz);
  vec3 l = 1.0 - g;
  vec3 i1 = min( g.xyz, l.zxy );
  vec3 i2 = max( g.xyz, l.zxy );

  //   x0 = x0 - 0.0 + 0.0 * C.xxx;
  //   x1 = x0 - i1  + 1.0 * C.xxx;
  //   x2 = x0 - i2  + 2.0 * C.xxx;
  //   x3 = x0 - 1.0 + 3.0 * C.xxx;
  vec3 x1 = x0 - i1 + C.xxx;
  vec3 x2 = x0 - i2 + C.yyy; // 2.0*C.x = 1/3 = C.y
  vec3 x3 = x0 - D.yyy;      // -1.0+3.0*C.x = -0.5 = -D.y

  // Permutations
  i = mod289(i);
  vec4 p = permute( permute( permute(
             i.z + vec4(0.0, i1.z, i2.z, 1.0 ))
           + i.y + vec4(0.0, i1.y, i2.y, 1.0 ))
           + i.x + vec4(0.0, i1.x, i2.x, 1.0 ));

  // Gradients: 7x7 points over a square, mapped onto an octahedron.
  // The ring size 17*17 = 289 is close to a multiple of 49 (49*6 = 294)
  float n_ = 0.142857142857; // 1.0/7.0
  vec3  ns = n_ * D.wyz - D.xzx;

  vec4 j = p - 49.0 * floor(p * ns.z * ns.z);  //  mod(p,7*7)

  vec4 x_ = floor(j * ns.z);
  vec4 y_ = floor(j - 7.0 * x_ );    // mod(j,N)

  vec4 x = x_ *ns.x + ns.yyyy;
  vec4 y = y_ *ns.x + ns.yyyy;
  vec4 h = 1.0 - abs(x) - abs(y);

  vec4 b0 = vec4( x.xy, y.xy );
  vec4 b1 = vec4( x.zw, y.zw );

  //vec4 s0 = vec4(lessThan(b0,0.0))*2.0 - 1.0;
  //vec4 s1 = vec4(lessThan(b1,0.0))*2.0 - 1.0;
  vec4 s0 = floor(b0)*2.0 + 1.0;
  vec4 s1 = floor(b1)*2.0 + 1.0;
  vec4 sh = -step(h, vec4(0.0));

  vec4 a0 = b0.xzyw + s0.xzyw*sh.xxyy ;
  vec4 a1 = b1.xzyw + s1.xzyw*sh.zzww ;

  vec3 p0 = vec3(a0.xy,h.x);
  vec3 p1 = vec3(a0.zw,h.y);
  vec3 p2 = vec3(a1.xy,h.z);
  vec3 p3 = vec3(a1.zw,h.w);

  //Normalise gradients
  vec4 norm = taylorInvSqrt(vec4(dot(p0,p0), dot(p1,p1), dot(p2, p2), dot(p3,p3)));
  p0 *= norm.x;
  p1 *= norm.y;
  p2 *= norm.z;
  p3 *= norm.w;

  // Mix final noise value
  vec4 m = max(0.6 - vec4(dot(x0,x0), dot(x1,x1), dot(x2,x2), dot(x3,x3)), 0.0);
  m = m * m;
  return 42.0 * dot( m*m, vec4( dot(p0,x0), dot(p1,x1),
                                dot(p2,x2), dot(p3,x3) ) );
}




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
			float d = distance(uLights[i].coord.xyz, vPosition);
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

float fog( float density ) {

  const float LOG2 = 1.442695;
  float x = vPosition.x;
  float y = vPosition.y;
  float z = vPosition.z;
  float fogFactor = exp2( -density * density * z * z * LOG2 );
  fogFactor *= snoise( vPosition * 0.01 );

  return clamp(fogFactor, 0.0, 1.0);

}


void main() {

  if ( uIsLine )
		fColor = vec4(1);
	else if ( !uCastsLight )
		fColor = texture(uTexture, vTexCoords);
	else {
		fColor = vec4(blinnPhong(), 1);
		fColor.xyz = mix( vec3( 0.97 ), fColor.xyz, fog( 0.01 ) );
	}

}
