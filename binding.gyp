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
      "src/IntervalPoint.cc"
    ]
  }]
}
