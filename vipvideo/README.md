pyinstaller -F -i [图标文件路径] [打包的py文件路径]


py2applet --make-setup vipvideo.py
rm -rf build dist
python setup.py py2app
