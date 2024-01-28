# skramm_BLEBeacon

## 概要

ソーシャル・イノベーションチャレンジ2023(https://www.oit.ac.jp/is/msl/soichalle/)で開発した成果物のうち、ビーコン側のプログラム

## 説明

- LINE BeaconをESP32で動かす
- 10秒毎に超音波センサーで距離を測定、3回距離を測定し、そのうち2回以上で近接と判定した場合に、LINE Beaconを発信する

## 使い方

### ESP32のセットアップ

1. 超音波センサー(HC-SR04)をESP32に接続する
    - echo: 18 ピン
    - trigger: 5 ピン
2. 適切なhwidを設定する
3. ESP32に書き込む