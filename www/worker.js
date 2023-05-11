self.gameWrapper;

self.Module = {
  locateFile: function (s) {
    console.log(s);
    return s;
  },
  onRuntimeInitialized: function () {
    console.log("WASM initialised");
    while (!self.gameWrapper) {}
    try {
      self.Module.canvas = self.gameWrapper.canvas;
      self.Module.setFps = (fps) => self.postMessage({ type: "fps", fps: fps });
      self.gameWrapper.run();
    } finally {
      self.gameWrapper.cleanup();
    }
  },
};

self.importScripts("bindings.js");

self.onmessage = (evt) => {
  const canvas = evt.data.canvas;
  self.gameWrapper = new GameWrapper(canvas);
};

class GameWrapper {
  constructor(canvas) {
    this.canvas = canvas;
    this.gameParams;
    this.game;
  }

  run() {
    console.log("Running", self.Module);
    this.gameParams = new self.Module.GameParams(
      this.canvas.width,
      this.canvas.height,
      90.0 // vfov
    );
    this.game = new self.Module.Game(this.gameParams);
    this.game.Run();
  }

  cleanup() {
    delete this.gameParams;
    delete this.game;
  }
}
