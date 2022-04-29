<?php
    $host = 'localhost'; //localhost
    $user = 'root'; //ID
    $pw = ''; //비밀번호
    $dbName = 'eu'; //DB이름
    $mysqli = new mysqli($host, $user, $pw, $dbName);
    
    //테이블 LIMIT해서 행 1줄 가져오게 함
    $sql = "SELECT sensor1, sensor2, sensor3, sensor4, sensor5, sensor6, sensor7, sensor8, sensor9, sensor10, sensor11, sensor12, sensor13, sensor14, sensor15, sensor16, sensor17, sensor18, sensor19, sensor20, sensor21, sensor22, sensor23, sensor24, sensor25, sensor26, sensor27, sensor28, sensor29, sensor30, sensor31 FROM eu LIMIT 1";
    $result = mysqli_query($mysqli, $sql);
    if (mysqli_num_rows($result) > 0) {
    while($row = mysqli_fetch_assoc($result)) {
        $sensor1 = $row['sensor1'];
        $sensor2 = $row['sensor2'];
        $sensor3 = $row['sensor3'];
        $sensor4 = $row['sensor4'];
        $sensor5 = $row['sensor5'];
        $sensor6 = $row['sensor6'];
        $sensor7 = $row['sensor7'];
        $sensor8 = $row['sensor8'];
        $sensor9 = $row['sensor9'];
        $sensor10 = $row['sensor10'];
        $sensor11 = $row['sensor11'];
        $sensor12 = $row['sensor12'];
        $sensor13 = $row['sensor13'];
        $sensor14 = $row['sensor14'];
        $sensor15 = $row['sensor15'];
        $sensor16 = $row['sensor16'];
        $sensor17 = $row['sensor17'];
        $sensor18 = $row['sensor18'];
        $sensor19 = $row['sensor19'];
        $sensor20 = $row['sensor20'];
        $sensor21 = $row['sensor21'];
        $sensor22 = $row['sensor22'];
        $sensor23 = $row['sensor23'];
        $sensor24 = $row['sensor24'];
        $sensor25 = $row['sensor25'];
        $sensor26 = $row['sensor26'];
        $sensor27 = $row['sensor27'];
        $sensor28 = $row['sensor28'];
        $sensor29 = $row['sensor29'];
        $sensor30 = $row['sensor30'];
        $sensor31 = $row['sensor31'];

        //출력
        echo $sensor1. $sensor2. $sensor3.$sensor4. $sensor5. $sensor6.$sensor7. $sensor8. $sensor9. $sensor10.$sensor11. $sensor12. $sensor13.$sensor14. $sensor15. $sensor16.$sensor17. $sensor18. $sensor19. $sensor20.$sensor21. $sensor22. $sensor23.$sensor24. $sensor25. $sensor26.$sensor27. $sensor28. $sensor29. $sensor30. $sensor31."<br>";
   }
   }else{
        echo "테이블에 데이터가 없습니다.";
   }
   mysqli_close($mysqli); // 디비 접속 닫기
?>