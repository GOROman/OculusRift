OculusCameraPlugin
==================

概要
----

Oculus Riftの頭の動きをMikuMikuMoving(MMM)内のカメラにリアルタイムで反映させるプラグインです。
裸眼立体や歪み補正のための画面のレンダリングには VIREio 等を利用してください。


ビルド方法
----------

+ OculusCameraPlugin/LibOVR フォルダへ Oculus SDK をコピーする

+ プロジェクト＞参照 から MikuMikuPlugin.dll と DxMath.dll を追加します (MikuMikuMovingのSystemフォルダにあります)


インストール方法
----------------

出来上がった OculusCameraPlugin.dll を MikuMikuMoving の Plugins フォルダにコピーします。


使用方法
--------

MikuMikuMovingを起動し、「プラグイン」タブの「Oculus Rift カメラ」をクリックして有効にします。


補足
----

MikuMikuMoving自体はC#で作られており、C#でのプラグイン実装をする必要がありますが、
Oculus SDKは C++ のため、C++/CLI でプラグインを作成しています。

今後の展望
----------

- XBox360等のジョイパッドに対応し、移動出来るようにする


