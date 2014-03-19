uniform sampler2DRect roundOne;
uniform float amount;

void main( void )
{

            vec2 st = gl_TexCoord[0].st;
            vec4 color;

            color += 1.0 * texture2DRect(roundOne, st + vec2(0.0, amount * 4.0));
            color += 2.0 * texture2DRect(roundOne, st + vec2(0.0, amount * 3.0));
            color += 3.0 * texture2DRect(roundOne, st + vec2(0.0, amount * 2.0));
            color += 4.0 * texture2DRect(roundOne, st + vec2(0.0, amount * 1.0));
            color += 5.0 * texture2DRect(roundOne, st + vec2(0.0, amount) );
            color += 4.0 * texture2DRect(roundOne, st + vec2(0.0, amount * -1.0));
            color += 3.0 * texture2DRect(roundOne, st + vec2(0.0, amount * -2.0));
            color += 2.0 * texture2DRect(roundOne, st + vec2(0.0, amount * -3.0));
            color += 1.0 * texture2DRect(roundOne, st + vec2(0.0, amount * -4.0));
            color /= 25.0;

            gl_FragColor = color;
}

