// 
// Especial thanks to https://github.com/saucecode/
//
// MeshBasicMaterial does not react to lighting 
// so we use MeshPhongMaterial
//------------------------------------------------------//

var scene = new THREE.Scene();
camera = new THREE.PerspectiveCamera(90, 1280/720, 0.1, 1000); // Could use window.innerWidth/window.innerHeight
var renderer = new THREE.WebGLRenderer();
document.body.appendChild(renderer.domElement);
renderer.setSize(1280, 720); // Could use (window.innerWidth, window.innerHeight)
scene.background = new THREE.Color('gray'); // set the background as gray
renderer.shadowMap.enabled = true; 
renderer.shadowMap.type = THREE.BasicShadowMap;

//------------------------------------------------------//

camera.position.z = -3; // set the camera position
camera.position.y = 1;  // a bit far from the center

//------------------------------------------------------//

var controls = new THREE.OrbitControls( camera, renderer.domElement ); // control de camera

//------------------------------------------------------//

floor = new THREE.Mesh(new THREE.PlaneGeometry(10,10, 10,10), 
                    new THREE.MeshPhongMaterial({color:0xffffff, depthWrite: false}));
floor.rotation.x -= Math.PI / 2; // rotates 90°
floor.position.y = -4; // move the ground lower
floor.receiveShadow = true; // Floor can have shadows cast onto it
scene.add(floor); // creates a ground white 10x10

//------------------------------------------------------//    

var cubeGeometry = new THREE.BoxGeometry(1, 1, 1);
var cubeMaterial = new THREE.MeshPhongMaterial({color: 0xaa22aa});
var cube = new THREE.Mesh(cubeGeometry, cubeMaterial);
scene.add(cube);
cube.reciveShadow = true;
cube.castShadow = true;
cube.position.x = .75;
//Creates an cube ^ | And an sphere v
var sphereGeometry = new THREE.SphereGeometry(.5,24,24);
var sphereMaterial = new THREE.MeshPhongMaterial({color: 0x22aaff});
var sphere = new THREE.Mesh(sphereGeometry, sphereMaterial);
scene.add(sphere);
sphere.position.x = -.75;
sphere.receiveShadow = true;
sphere.castShadow = true;
var angObj = 0;

//------------------------------------------------------//

light1 = new THREE.PointLight(0xffffff, 1, 20);
light1.position.set(-2,2,0);
light1.castShadow = true;
light1.shadow.camera.near = 0.1; // Will not light anything closer than 0.1 units 
light1.shadow.camera.far = 10; // or further than 25 units
scene.add(light1);
var lightSphere1 = new THREE.Mesh(new THREE.SphereGeometry(0.125,10,0.25), 
                                new THREE.MeshBasicMaterial( {color: 0xffff00}));
lightSphere1.position.x = -2;
lightSphere1.position.y = 2;
lightSphere1.position.z = 0;
scene.add(lightSphere1);

// Creates 2 sources of light that irradiates 360°

light2 = new THREE.PointLight(0xffffff, 1, 20);
light2.position.set(-2,2,0);
light2.castShadow = true;
light2.shadow.camera.near = 0.1;
light2.shadow.camera.far = 10; 
scene.add(light2);
var lightSphere2 = new THREE.Mesh(new THREE.SphereGeometry(0.125,10,0.25), 
                                new THREE.MeshBasicMaterial( {color: 0xffff00}));
lightSphere2.position.x = -2;
lightSphere2.position.y = 2;
lightSphere2.position.z = 0;
scene.add(lightSphere2);
var anglight = 0;

//------------------------------------------------------//

var animate = function() {
    requestAnimationFrame(animate); // needed to work

    controls.update(); // needed to move the camera

    animateLightSpheres();
    animateCubeSphere();
    renderer.render(scene, camera); // needed to work
};

function animateCubeSphere(){ // rotates both cube and sphere
    angObj += 0.005;
    sphere.rotation.x = angObj+0.01;
    sphere.rotation.y = 1;
    sphere.rotation.z = 1;

    cube.rotation.x = -angObj+0.01;
    cube.rotation.y = 1;
    cube.rotation.z = 1;
}

function animateLightSpheres(){
    anglight += 0.004; 
        
    lightSphere1.position.x = Math.cos(anglight)*2;
    lightSphere1.position.y = Math.sin(anglight)*2; // needed to move in circles

    lightSphere2.position.x = Math.cos(anglight/2.2)*2; // same but slower
    lightSphere2.position.y = Math.sin(anglight/2.2)*2;

    light1.position.x = lightSphere1.position.x; // The position of the light
    light1.position.y = lightSphere1.position.y; // will be always the same of
    light1.position.z = lightSphere1.position.z; // the sphere that is moving 
    light2.position.x = lightSphere2.position.x; // with it.
    light2.position.y = lightSphere2.position.y; 
    light2.position.z = lightSphere2.position.z; 
}                                                
animate();

// var select = 0;
function onKeyDown(event) {
    var keyCode = event.which;

};
document.addEventListener("keydown", onKeyDown, false);