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

const points = [
    new m.Point(1, 1.3),
    new m.Point(2, 3.5),
    new m.Point(3, 4.2),
    new m.Point(4, 5.0),
    new m.Point(5, 7.0),
    new m.Point(6, 8.8),
    new m.Point(7, 10.1),
    new m.Point(8, 12.5),
    new m.Point(9, 13.0),
    new m.Point(10, 15.6)
]

const lsa = new m.Lsa()
for (var i = 0; i < points.length; i++) {
    lsa.addPoint(points[i]);
}
console.log(lsa.calculateA0());
console.log(lsa.calculateA1());

const ip1 = new m.IntervalPoint(1, 1);
const ip2 = new m.IntervalPoint(2.43, 2.43);

console.log(ip2.getLowerX());
console.log(ip2.getUpperX());
console.log(ip2.getLowerY());
console.log(ip2.getUpperY());

const factory = new m.PointFactory("RPS", "");
console.log(factory);
const randomPoints = factory.generatePoints(10, 1, 100);
console.log(randomPoints);

const intervalFactory = new m.PointFactory("RPS", "interval");
console.log(intervalFactory);
const randomIntervalPoints = intervalFactory.generatePoints(10, 1, 100);
console.log(randomIntervalPoints);

