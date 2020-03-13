/**
 * 
 * Credits: https://dev.to/maniflames/creating-a-custom-shader-in-threejs-3bhi
 */

window.addEventListener('load', init);

let scene;
let camera;
let renderer;

let uniforms = {
    colorA: { type: 'vec3', value: new THREE.Color(0xff0000) },
    colorB: { type: 'vec3', value: new THREE.Color(0x00ff00) }
};

let vertexShader = `
    varying vec4 modelViewPosition; 

    void main() {
        modelViewPosition = modelViewMatrix * vec4(position, 1.0);
        gl_Position = projectionMatrix * modelViewPosition; 
    }
`;

let fragmentShader = `
    uniform vec3 colorA; 
    uniform vec3 colorB; 

    void main() {
        vec3 finalColor = colorA + colorB;
        gl_FragColor = vec4(finalColor, 1.0);
    }
`;

function init() {
    scene = new THREE.Scene();
    camera = new THREE.PerspectiveCamera(75, window.innerWidth / window.innerHeight, 0.1, 1000);
    camera.position.z = 5;

    renderer = new THREE.WebGLRenderer();
    renderer.setSize(window.innerWidth, window.innerHeight);
    document.body.appendChild(renderer.domElement);
    
    addBasicCube();
    addShadingCube();

    animationLoop();
}

function addBasicCube() {
    let geometry = new THREE.BoxGeometry(1, 1, 1);
    var material = new THREE.MeshBasicMaterial({color: 0x0000ff});

    let mesh = new THREE.Mesh(geometry, material);
    mesh.position.x = -2;
    scene.add(mesh);
}

function addShadingCube() {
    uniforms.colorA = { type: 'vec3', value: new THREE.Color(0xff0000) };
    uniforms.colorB = { type: 'vec3', value: new THREE.Color(0x00ff00) };

    let geometry = new THREE.BoxGeometry(1, 1, 1);

    let material = new THREE.ShaderMaterial({
        uniforms: uniforms,
        fragmentShader: fragmentShader,
        vertexShader: vertexShader,
    });

    let mesh = new THREE.Mesh(geometry, material);

    mesh.position.x = 2;
    scene.add(mesh);
}

function animationLoop() {
    renderer.render(scene, camera);

    scene.traverse(function(node) {
        if(node instanceof THREE.Mesh) {
            node.rotation.x += 0.01;
            node.rotation.y += 0.03;
        }
    });

    requestAnimationFrame(animationLoop);
}
