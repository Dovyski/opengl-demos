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
floor.position.y = -1;
floor.receiveShadow = true; // Floor can have shadows cast onto it
scene.add(floor);
//

ambientLight = new THREE.AmbientLight(0xffffff, 0.2);
scene.add(ambientLight);
	
light = new THREE.PointLight(0xffffff, 0.8, 18);
light.position.set(-3,6,-3);
light.castShadow = true;
light.shadow.camera.near = 0.1; // Will not light anything closer than 0.1 units 
light.shadow.camera.far = 25; // or further than 25 units
scene.add(light);




var geometry = new THREE.BoxGeometry(1, 1, 1);
var material = new THREE.MeshPhongMaterial({color: 0xaa22aa});
var cube = new THREE.Mesh(geometry, material);
scene.add(cube);
cube.reciveShadow = true;
cube.castShadow = true;

var animate = function() {
    requestAnimationFrame(animate);

    controls.update();

    renderer.render(scene, camera);
};


animate();
// var select = 0;
function onKeyDown(event) {
    var keyCode = event.which;

};
document.addEventListener("keydown", onKeyDown, false);