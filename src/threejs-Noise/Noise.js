var scene = new THREE.Scene();
camera = new THREE.PerspectiveCamera(90, 1280/720, 0.1, 1000); // Could use window.innerWidth/window.innerHeight
var renderer = new THREE.WebGLRenderer();
document.body.appendChild(renderer.domElement);
var controls = new THREE.OrbitControls( camera, renderer.domElement ); // control de camera

scene.background = new THREE.Color('gray'); // set the background as gray
renderer.shadowMap.enabled = true; 
renderer.shadowMap.type = THREE.BasicShadowMap;

camera.position.z = -1; // set the camera position
camera.position.y = 0;  // a bit far from the center

light1 = new THREE.PointLight(0xffffff, 1, 20);
light1.position.set(-2,2,0);
light1.castShadow = true;
light1.shadow.camera.near = 0.1; // Will not light anything closer than 0.1 units 
light1.shadow.camera.far = 10; // or further than 25 units
scene.add(light1);


//
var x=-1.5;
var y=0;
var points = [];
//

var setup = function(){
    renderer.setSize(window.innerWidth, window.innerHeight); // Could use (1280, 720)
    draw();
}

var draw = function(){

    var material = new THREE.LineBasicMaterial( { color: 0xFFaa33 } );
    for(x; x<1.5; x+=.05){
            var z = Math.random();
            // var z = PerlinNoise(x,y);
            z-=.25; 
            points.push( new THREE.Vector3( x, z, y) );
    } 
    var geometry = new THREE.BufferGeometry().setFromPoints( points );

    var line = new THREE.Line( geometry, material );
    scene.add( line );

}

// PERLIN NOISE

// var lerp = function(a0, a1, w){ return ((1.0 - w)*a0 + w*a1);}

// var dotGridGradient = function(ix, iy, x, y){
 
//     var Gradient = [1280][720][2]

//     var dx = x - ix;
//     var dy = y - iy;
//     return (dx*Gradient[iy][ix][0] + dy*Gradient[iy][ix][1]);
// }

// var PerlinNoise = function(x, y){

//     var x0 = x;
//     var x1 = x0 + 1; // OLHO NO 1
//     var y0 = y;
//     var y1 = y0 + 1; // OLHO NO 1

//     var sx = x - x0;
//     var sy = y - y0;
    
//     var n0, n1, ix0, ix1, value;

//     n0 = dotGridGradient(x0, y0, x, y);
//     n1 = dotGridGradient(x1, y0, x, y);
//     ix0 = lerp(n0, n1, sx);

//     n0 = dotGridGradient(x0, y1, x, y);
//     n1 = dotGridGradient(x1, y1, x, y);
//     ix1 = lerp(n0, n1, sx);

//     value = lerp(ix0, ix1, sy);
//     return value;
// }

// PERLIN NOISE


var animate = function() {
    requestAnimationFrame(animate); // needed to work

    controls.update(); // needed to move the camera
    setup();

    renderer.render(scene, camera); // needed to work
};


animate();


function onKeyDown(event) {
    var keyCode = event.which;

};
document.addEventListener("keydown", onKeyDown, false);