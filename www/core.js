const worker = new Worker("worker.js");

window.onload = () => {
  const offscreen = document
    .querySelector("canvas")
    .transferControlToOffscreen();
  worker.postMessage({ canvas: offscreen }, [offscreen]);
};

worker.onmessage = (e) => {
  if (e.data.type === "fps") {
    document.getElementById("fps").innerText = `FPS: ${e.data.fps.toFixed(2)}`;
  }
};
