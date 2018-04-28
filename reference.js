function recycle (x, n) {
  if (Object.getPrototypeOf(x) !== Array.prototype) x = [ x ]
  
  // preliminary js implementation
  for (var i = 0, j = 0, y = Array(n); j < n; i++, j++) {
    if (i === x.length) i = 0
    y[j] = x[i]
  }
  //
  
  return y
}

module.exports = recycle