// 
// Especial thanks to https://github.com/saucecode/
//
// MeshBasicMaterial does not react to lighting 
// so we replace with MeshPhongMaterial

var scene = new THREE.Scene();
camera = new THREE.PerspectiveCamera(90, 1280/720, 0.1, 1000);
var renderer = new THREE.WebGLRenderer();
document.body.appendChild(renderer.domElement);
renderer.setSize(1280, 720);
scene.background = new THREE.Color('white');
renderer.shadowMap.enabled = true;
renderer.shadowMap.type = THREE.BasicShadowMap;
//
camera.position.z = -3;
camera.position.y = 1;
//
var controls = new THREE.OrbitControls( camera, renderer.domElement );
//
floor = new THREE.Mesh(new THREE.PlaneGeometry(10,10, 10,10), 
                       new THREE.MeshPhongMaterial({color:0xffffff, depthWrite: false}));
floor.rotation.x -= Math.PI / 2;
floor.position.y = -4;
floor.receiveShadow = true; // Floor can have shadows cast onto it
scene.add(floor);
//

// ambientLight = new THREE.AmbientLight(0xffffff, 0.2);
// scene.add(ambientLight);
	
light1 = new THREE.PointLight(0xffffff, 1, 20);
light1.position.set(-2,2,0);
light1.castShadow = true;
light1.shadow.camera.near = 0.1; // Will not light anything closer than 0.1 units 
light1.shadow.camera.far = 25; // or further than 25 units
scene.add(light1);
var lightSphere1 = new THREE.Mesh(new THREE.SphereGeometry(0.125,10,0.25), 
                                new THREE.MeshBasicMaterial( {color: 0xffff00}));
lightSphere1.position.x = -2;
lightSphere1.position.y = 2;
lightSphere1.position.z = 0;
scene.add(lightSphere1);
var anglight1 = 0;


//

light2 = new THREE.PointLight(0xffffff, 1, 20);
light2.position.set(-2,2,0);
light2.castShadow = true;
light2.shadow.camera.near = 0.1; // Will not light anything closer than 0.1 units 
light2.shadow.camera.far = 25; // or further than 25 units
scene.add(light2);
var lightSphere2 = new THREE.Mesh(new THREE.SphereGeometry(0.125,10,0.25), 
                                new THREE.MeshBasicMaterial( {color: 0xffff00}));
lightSphere2.position.x = -2;
lightSphere2.position.y = 2;
lightSphere2.position.z = 0;
scene.add(lightSphere2);
var anglight2 = 0;



var geometry = new THREE.BoxGeometry(1, 1, 1);
var material = new THREE.MeshPhongMaterial({color: 0xaa22aa});
var cube = new THREE.Mesh(geometry, material);
scene.add(cube);
cube.reciveShadow = true;
cube.castShadow = true;

var animate = function() {
    requestAnimationFrame(animate);

    controls.update();

    animateLightSpheres();
    renderer.render(scene, camera);
};

function animateLightSpheres(){
    anglight1 += 0.004;
    anglight2 += 0.008;
        
    lightSphere1.position.x = Math.cos(anglight1)*2;
    lightSphere1.position.y = Math.sin(anglight1)*2;

    lightSphere2.position.x = Math.cos(anglight1/2.2)*2;
    lightSphere2.position.y = Math.sin(anglight1/2.2)*2;


    light1.position.x = lightSphere1.position.x;
    light1.position.y = lightSphere1.position.y;
    light1.position.z = lightSphere1.position.z;

    light2.position.x = lightSphere2.position.x;
    light2.position.y = lightSphere2.position.y;
    light2.position.z = lightSphere2.position.z;

}
animate();
// var select = 0;
function onKeyDown(event) {
    var keyCode = event.which;

};
document.addEventListener("keydown", onKeyDown, false);