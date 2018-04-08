{
  "targets": [{
    "target_name": "ean-native",
    "include_dirs" : [
      "src",
      "<!(node -e \"require('nan')\")"
    ],
    "sources": [
      "src/index.cc",
      "src/Vector.cc",
      "src/Point.cc",
      "src/Lsa.cc"
    ]
  }]
}
