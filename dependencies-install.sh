wget https://bootstrap.pypa.io/pip/2.7/get-pip.py
sudo python2 get-pip.py
# upgrade setup tools to avoid "invalid command egg_info" error
pip2 install --upgrade setuptools
# install python-dev to avoid "x86_64-linux-gnu-gcc failed..." error
sudo apt-get install python2-dev
pip2 install pycrypto
pip2 install distorm3
git clone https://github.com/volatilityfoundation/volatility.git
sudo mkdir /opt/volatility
sudo mv ~/Downloads/volatility /opt/volatility
sudo apt install hashcat



