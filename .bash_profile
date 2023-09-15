# .bash_profile

# Get the aliases and functions
if [ -f ~/.bashrc ]; then
	. ~/.bashrc
fi

# User specific environment and startup programs

export PATH=/home/devapp/app/bin:$PATH
LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/devapp/app/bin
export LD_LIBRARY_PATH