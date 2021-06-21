# マルチプラットフォーム用コンポーネント

## 概要

emscripten, DxLib for HTML5 を使って WebGL + WebAssembly アプリケーションを作成できるように
Visual Studio Code の設定を済ませたパッケージ.
Android,iOSでも使用できるように作ります。
作成予定のコンポーネントは

・firebaseによる通信対戦
・ビットマップフォント（以下BMフォント）及びアニメーション
・ローカライズ機能（BMフォントにも適用）
・バッテリー情報取得機能（Android,iOSのみ）
・通信情報取得機能
・ブラウザの画面が伸び縮みしても適用機能
・Android,iOSの画面比率によるパーティションの適用
・Flutbufferファイルの採用（jsonだと重いため）
・Box２Dの採用
・ボタンコンポーネント、ウィンドウコンポーネントの多数作成
・SpriteStudio5との連携

## 注意点
・Emscriptenはリンクする順序によってエラーが出るのでよく注意する。
・描画系の処理は座標系が崩れていることから、全てラッピングする。
・新しいクラスを追加したらtask.jsonに追加を忘れない。
・新しいコンポーネントフォルダを作成したらcompile.shに追加するのを忘れない。

## 作成しての感想
2021.6.13
・縦画面はスマホでない限りブラウザだと寂しい。ブラウザは横方向にパーティションを入れるべき
(1514*1136が妥当？だとすると、パーティションが片面437px、両面で874pxあることに。専用にSpriteStudioなどでアニメしないとダメだろう・・・)

## 前提要件

- Visual Studio Code (1.42.1 で動作確認済み)
- [emscripten 2.0.4](https://emscripten.org)

emscripten の導入は <https://qiita.com/nokotan/items/5fa6f2d39ff7bb6641e8> や
<https://www.slideshare.net/llamerada-jp/cmu29> (やや読破難度高いスライド) が参考になると思います.

## 推奨インストール

### C/C++ インテリセンス

- [C/C++ VSCode Extension](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools)

### デバッグ用の拡張機能

- [Debugger for Chrome](https://marketplace.visualstudio.com/items?itemName=msjsdiag.debugger-for-chrome)
- [Debugger for Firefox](https://marketplace.visualstudio.com/items?itemName=firefox-devtools.vscode-firefox-debug)
- [Live Server](https://marketplace.visualstudio.com/items?itemName=ritwickdey.LiveServer)

## ビルド

- Ctrl(Cmd)+Shift+B (デバッグビルド)
- リリースビルドをしたいときは Ctrl(Cmd)+Shift+P でタスクの実行を選んで, Build Release

## 実行

- Ctrl(Cmd)+Shift+P でタスクの実行を選んで, Run Local Server and Open Browser
- Debugger for Chrome または Debugger for Firefox をインストール済みであれば Ctrl(Cmd)+Shift+P でタスクの実行を選んで, Run Local Server を選んだ後, デバッグの開始でデバッグができます

## デバッグ

- デバッグビルド時は C++ に対する SourceMap が有効になるので, C++ ソースファイル上にブレークポイントが仕掛けられます
- ただ, 変数ウォッチは機能しているか怪しい模様

## 質問点など

- To be announced...

## ライセンス表記

- MIT ライセンスにて配布します (基本的に何でもできると思います; 継承すべきライセンスも大丈夫だと思う...たぶん)
- 依存ライブラリのライセンスなどは LICENSE.txt を参照のこと
- DxLib for HTML5 を使った Web アプリに必要なライセンス表記は, freetype を除いて DxLib と同じなので参考までに

## 謝辞

- デフォルトのフォントとして同梱させてもらっているフォント (ロゴたいぷゴシック) のサイトです. <http://www.fontna.com/blog/1226/>
- 移植元のDXライブラリのサイトです. <https://dxlib.xsrv.jp/>
- emscripten のサイトです. <https://emscripten.org/>

これらのプロジェクトのおかげで DxLib for HTML5 は成り立っています. ありがとうございます.

- - -

DxLib for HTML5  Copyright (C) 2021 かめのこにょこにょこ
