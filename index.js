var { _recycle } = require('node-gyp-build')(__dirname)
var { isNumber } = require('util')

function isFloat32Array (x) {
  return x && Object.getPrototypeOf(x) === Float32Array.prototype
}

function isNumericArray (x) {
  return x && Object.getPrototypeOf(x) === Array.prototype && x.every(isNumber)
}

function isUint (n) {
  return n && Object.getPrototypeOf(n) === Number.prototype &&
    n >= 0 && n % 1 === 0
}

// x: Float32Array | Number[], n: Number
function recycle (x, n) {
  if (!isFloat32Array(x)) {
    if (isNumericArray(x)) x = new Float32Array(x)
    else throw new TypeError('Float32Array-like required for parameter x')
  }
  if (!isUint(n)) throw new TypeError('unsigned int required for parameter n')
  return _recycle(x, n)
}

module.exports = recycle
