#!/bin/sh
# $Id: weather.sh,v 1.1 2002/03/07 15:13:46 in2 Exp $
#
bin/weather.perl
bin/post Record 全省今日各地天氣預報 [氣象小姐] etc/weather.today
bin/post Record 全省明日各地天氣預報 [氣象小姐] etc/weather.tomorrow
