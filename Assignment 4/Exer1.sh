_user=$(whoami)
_hostname=$(hostname)
_currdate=$(date)
echo "============================================================"
echo " "
echo " Welcome $_user to $_hostname server"
echo " Curr. time: $_currdate"
h=$(date +"%H")
if [ $h -gt 5 -a $h -le 12 ]; then
echo " Good Morning $_user"
elif [ $h -gt 12 -a $h -le 18 ];then
echo " Good Afternoon $_user"
elif [ $h -gt 18 -a $h -le 24 ]; then
echo " Good Evening $_user"
else
echo " It is too late $_user !Go to sleep!"
fi
echo " "
echo "============================================================"