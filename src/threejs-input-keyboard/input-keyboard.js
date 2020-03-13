/**
 * 
 */

var scene = new THREE.Scene();
var camera = new THREE.PerspectiveCamera(75, window.innerWidth/window.innerHeight, 0.1, 1000);

var renderer = new THREE.WebGLRenderer();
renderer.setSize(window.innerWidth, window.innerHeight);
document.body.appendChild(renderer.domElement);

var geometry = new THREE.BoxGeometry(1, 1, 1);
var material = new THREE.MeshBasicMaterial({color: 0xff0000});
var cube = new THREE.Mesh(geometry, material);
scene.add(cube);

camera.position.z = 5;

var animate = function() {
    requestAnimationFrame(animate);

    cube.rotation.x += 0.01;
    cube.rotation.y += 0.01;

    renderer.render(scene, camera);
};

animate();

function onKeyDown(event) {
    var keyCode = event.which;
    var speed = 0.1;

    console.log('keyCode', keyCode);

    if (keyCode == 87) {
        cube.position.y += speed;
    } else if (keyCode == 83) {
        cube.position.y -= speed;
    } else if (keyCode == 65) {
        cube.position.x -= speed;
    } else if (keyCode == 68) {
        cube.position.x += speed;
    } else if (keyCode == 32) {
        cube.position.set(0, 0, 0);
    }
};

document.addEventListener("keydown", onKeyDown, false);
