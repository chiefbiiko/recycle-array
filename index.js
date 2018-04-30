var { _recycle } = require('node-gyp-build')(__dirname)
var { isNumber } = require('util')

function isFloat32Array (x) {
  return x && Object.getPrototypeOf(x) === Float32Array.prototype
}

function isUint (n) {
  return isNumber(n) && n >= 0 && n % 1 === 0
}

function recycle (x, n) {
  if (!isFloat32Array(x)) {
    try {
      x = new Float32Array(x)
    } catch (_) {
      throw new TypeError('Float32Array-like required for parameter x')
    }
  }
  if (!isUint(n)) {
    throw new TypeError('unsigned int required for parameter n')
  }
  return _recycle(x, n)
}

module.exports = recycle
