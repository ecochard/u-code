import * as Math from "math";


print( Math.sin(5.5), "\n" );

/*
let start = now( );
for( let i=0; i<10000000; i++ ) {
}
print( now()-start, "ms\n" );
*/

function test( ) {
	let zz = 0;

	return {
		inc: function( ) {
			return ++zz;
		},
		toString: function( ) {
			return "test value = "+zz;
		}
	}
}

const t = [ "55", "5555" ];

proto( t, {
	length: function( ) { 
		return length(this);
	},
	toString: function( ) {
		print( "here" );
	}
});

print( ">", t, "\n" );
print( ">", t.length(), "\n" );

