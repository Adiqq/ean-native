{
  "targets": [{
    "target_name": "ean-native",
    "include_dirs" : [
      "src",
      "<!(node -e \"require('nan')\")"
    ],
    'cflags!': [ '-fno-exceptions' ],
    'cflags_cc!': [ '-fno-exceptions' ],
    "sources": [
      "src/index.cc",
      "src/Vector.cc",
      "src/Point.cc",
      "src/Lsa.cc",
      "src/LsaInterval.cc",
      "src/IntervalPoint.cc",
      "src/PointFactory.cc",
      "src/RandomPointStrategy.cc"
    ],
    "conditions" : [
      ['OS=="win"', {
        'include_dirs' : [
          'C:\\Program Files\\boost\\boost_1_67_0'
        ]
      }]
    ]
  }]
}
