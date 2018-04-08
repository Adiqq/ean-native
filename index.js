// this is how we will require our module
const m = require('./')

const vec1 = new m.Vector(20, 10, 0)
console.log(vec1) // Vector { x: 20, y: 10, z: 0 }

const vec2 = new m.Vector(0, 0, 0)
vec2.x = 30
vec2.z = 100
console.log(vec2) // Vector { x: 30, y: 0, z: 100 }

const vecSum = vec1.add(vec2)
console.log(vecSum) // Vector { x: 50, y: 10, z: 100 }

const p1 = new m.Point(1, 1)
const p2 = new m.Point(2, 2)
const p3 = new m.Point(3, 3)

const lsa = new m.Lsa()
lsa.addPoint(p1);
lsa.addPoint(p2);
lsa.addPoint(p3);
console.log(lsa.calculateA0());
console.log(lsa.calculateA1());