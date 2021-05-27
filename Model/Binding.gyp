{
  "targets": [
    {
      "target_name": "AnomalyDetector",
      "cflags!": [ "-fno-exceptions" ],
      "cflags_cc!": [ "-fno-exceptions" ],
      "sources": [
        "./src/timeseries.cpp",
        "./src/anomaly_detection_util.cpp",
        "./src/minCircle.cpp",
        "./src/SimpleAnomalyDetector.cpp",
        "./src/HybridAnomalyDetector.cpp",
        "./src/index.cpp"
      ],
      "include_dirs": [
        "<!@(node -p \"require('node-addon-api').include\")"
      ],
      'defines': [ 'NAPI_DISABLE_CPP_EXCEPTIONS' ],
    }
  ]
}