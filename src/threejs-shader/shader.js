/**
 * 
 * Credits: https://dev.to/maniflames/creating-a-custom-shader-in-threejs-3bhi
 */

window.addEventListener('load', init);

let scene
let camera
let renderer
let sceneObjects = []
let uniforms = {}

function init() {
    scene = new THREE.Scene()

    camera = new THREE.PerspectiveCamera(75, window.innerWidth / window.innerHeight, 0.1, 1000)
    camera.position.z = 5

    renderer = new THREE.WebGLRenderer()
    renderer.setSize(window.innerWidth, window.innerHeight)

    document.body.appendChild(renderer.domElement)
    
    addBasicCube()
    addExperimentalCube()

    animationLoop()
}

function addBasicCube() {
    let geometry = new THREE.BoxGeometry(1, 1, 1);
    let material = new THREE.ShaderMaterial();

    let mesh = new THREE.Mesh(geometry, material)
    mesh.position.x = -2
    scene.add(mesh)
    sceneObjects.push(mesh)
}

function vertexShader() {
    return `
    varying vec4 modelViewPosition; 

    void main() {
      modelViewPosition = modelViewMatrix * vec4(position, 1.0);
      gl_Position = projectionMatrix * modelViewPosition; 
    }
    `;
}

function fragmentShader() {
    return `
      uniform vec3 colorA; 
      uniform vec3 colorB; 

      void main() {
        vec3 finalColor = colorA + colorB;
        gl_FragColor = vec4(finalColor, 1.0);
      }
    `;
}


function fragmentShaderOneColorOnly() {
    return `
      uniform vec3 colorA; 
      uniform vec3 colorB; 

      void main() {
        gl_FragColor = vec4(colorA, 1.0);
      }
    `;
}

function addExperimentalCube() {
    uniforms.colorA = { type: 'vec3', value: new THREE.Color(0xff0000) }
    uniforms.colorB = { type: 'vec3', value: new THREE.Color(0x00ff00) }

    let geometry = new THREE.BoxGeometry(1, 1, 1);

    let material = new THREE.ShaderMaterial({
        uniforms: uniforms,
        fragmentShader: fragmentShader(),
        vertexShader: vertexShader(),
    });

    let mesh = new THREE.Mesh(geometry, material);

    mesh.position.x = 2;
    scene.add(mesh);
    sceneObjects.push(mesh);
}

function addExperimentalLightCube() {
    uniforms.colorA = { type: 'vec3', value: new THREE.Color(0x74ebd5) }
    uniforms.colorB = { type: 'vec3', value: new THREE.Color(0xACB6E5) }

    let geometry = new THREE.BoxGeometry(1, 1, 1)
    let material = new THREE.ShaderMaterial({
        uniforms: uniforms,
        fragmentShader: fragmentShaderOneColorOnly(),
        vertexShader: vertexShader(),
        lights: true
    })

    let mesh = new THREE.Mesh(geometry, material)
    mesh.position.x = 2
    scene.add(mesh)
    sceneObjects.push(mesh);
}


function animationLoop() {
    renderer.render(scene, camera)

    for (let object of sceneObjects) {
        object.rotation.x += 0.01;
        object.rotation.y += 0.03;
    }

    requestAnimationFrame(animationLoop)
}

