# CPP_DecisionTree

## 介紹
決策樹(Decision Tree)可以解決分類問題，其利用已知分類的實例，歸納出實例裡類別與屬性之間的隱藏規則後，建立樹狀結構。決策樹可對相似的實例進行分類或預測。
[學習資料](http://debussy.im.nuu.edu.tw/sjchen/MachineLearning/final/CLS_DT.pdf)

## 目標
分類問題：評估天氣是否適合打網球<br>
分類類別：Yes、No<br>
資料集：14筆已分類天氣實例<br>
資料集內容：<br>
![image](https://github.com/leodflag/CPP_DecisionTree/blob/master/img/data.png)

演算法：使用ID3計算資訊獲利熵(Entropy)衡量屬性分類資料的能力，資訊獲利最大值(Gain)的屬性當分類依據。<br>
公式<br>
![image](https://github.com/leodflag/CPP_DecisionTree/blob/master/img/Entropy.png)<br>
![image](https://github.com/leodflag/CPP_DecisionTree/blob/master/img/Gain.png)

## 計算範例
![image](https://github.com/leodflag/CPP_DecisionTree/blob/master/img/ID3.png)
## 設計架構
在決策樹內存入所有資訊，架構龐大複雜

### 決策樹結構
![image](https://github.com/leodflag/CPP_DecisionTree/blob/master/img/Data_Str.png)
![image](https://github.com/leodflag/CPP_DecisionTree/blob/master/img/goalData.png)
![image](https://github.com/leodflag/CPP_DecisionTree/blob/master/img/DecisionTree.png)
![image](https://github.com/leodflag/CPP_DecisionTree/blob/master/img/NODE.png)

決策樹的一個node<br>
![image](https://github.com/leodflag/CPP_DecisionTree/blob/master/img/one%20node.png)

## 設計說明(部份函式)

    main：演算法架構
        1. 讀取檔案資料
        2. 找到最大的資訊獲利值
        3. 建樹(建立根節點)
        4. 取得最大資訊獲利值屬性的內部屬性陣列
        5. 查看根節點的左中右指標指向，若為空，則令4.的內部屬性陣列對應位置值設空字串
        6. 根據根節點的內部屬性建立屬性小表
        7. 找到最大資訊獲利的屬性
        8. 檢查Yes跟No數量，較大的則為存入左中右指向資料
        9. 建樹
        10. 重複6.到9.，直到內部屬性陣列完成
        11. 中序走訪印出決策樹

    isTreeEmpty：判斷決策樹是否是空的

    createTreeNode：
        1. 建立Yes、No和新節點
        2. 查看新節點的左、中、右指標是否指向Yes或No，是則連接，不是則指向空字串
        3. 若樹不存在則建立根節點，否則依序查看左中右的指向是否為空，若為空則加上新節點

    findMaxGain：
        1. 輸入資料矩陣
        2. 取得每行屬性
        3. 找出所有屬性的資料
        4. 取得節點的資訊獲利值
        5. 找出根節點資訊獲利最大值

    make_goal_data：建立內部屬性的小表

    returnGoalArray：取得目標直行的不重複內部屬性，存成字串陣列

    find_yes_no：找出對應的類別，製作出目標屬性表單

    findgoalS：計算目標屬性與內部屬性的Gain值
        1. 建立樹節點
        2. 將載入的屬性陣列存入樹節點
        3. 存入左中右屬性
        4. 找出類別並計算個數

    GO：輸入最大資訊獲利欄的字串串列以建造樹

    Entropy_function：輸入類別的數量，計算熵

    inOrder：中序走訪
    走完左子樹，再走中子樹，最後右子樹

## 結果
![image](https://github.com/leodflag/CPP_DecisionTree/blob/master/img/Decision%20Tree%20inOrder.png)
## 改進設計架構虛擬碼

決策樹架構簡化：只存最終分類結果資料
計算最大資訊獲利值：改以條件搜尋資料表內容，並計算最大資訊獲利值

    1. 依條件取得天氣資料
    2. 找出最大獲利屬性
    3. 建立決策樹
    4. 重複1.到3.，直到分類完成
