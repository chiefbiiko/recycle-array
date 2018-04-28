var tape = require('tape')
var ref = require('./reference')

tape('reference', function (t) {
  t.same(ref([ 419, 44 ], 5), [ 419, 44, 419, 44, 419 ], 'recycles')
  t.end()
})
