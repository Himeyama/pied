# PIED

## 概要
パレット(Palette)から画像(Image)を誤差拡散法(Error Diffusion)で再構成するプログラムです。

## 依存環境
- OpenCV4
```sh
sudo apt install libopencv-dev
```

## 動作確認
- Ubuntu 20.04

## リポジトリーをクローン
```sh
git clone https://github.com/Himeyama/pied
cd pied
```

## インストール
```sh
make
sudo make install
```

## コマンド
```sh
pied [入力画像ファイル名] [出力画像ファイル名] [パレット画像ファイル名] 
```

## 備考
パレット画像は縦1pxで横長のものです。`color_palette.png`がそれです。