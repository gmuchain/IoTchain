/**
 * @author v.lugovsky
 * created on 16.12.2015
 */
(function () {
  'use strict';

  angular.module('IotChainDashboard.pages.transactions-table')
      .controller('TransactionsTableCtrl', TransactionsTableCtrl);

  /** @ngInject */
  function TransactionsTableCtrl($scope, $filter, $http,$timeout,editableOptions, editableThemes,sharedProperties) {

    $scope.transactionsPageSize = 20;
    $scope.Transactions = []
    $http.get('/assets/test.json').success(function (data){
      //$http.get('http://tree.star.is/public/block_format.json').success(function (data){
        var blocks = [];
        var transactionArr = [];
        for(var i = 0; i < data.length; i++){
            var blockTransactions = data[i].transactions;
            for(var j = 0; j < blockTransactions.length; j++){
              transactionArr.push(blockTransactions[j]);
            }
            //TODO: sort by transaction time
            //$scope.Transactions.push(transactionArr);
        };
        
        $timeout(function() {
          $scope.Transactions = transactionArr;
          console.log("digest");         
          // anything you want can go here and will safely be run on the next digest.
          $scope.$apply();
          $scope.$digest();
          console.log($scope.Transactions.length);
          
        });
      });





    var smartTableData2 = [];
    for(var i=0;i<20;i++) {
      var tempHash = "hash" + i;
        smartTableData2.push({
            id: i,
            hash: tempHash,
            age: '2s',
            data: 'test data',
            amount: "512"
          });
      }
    $scope.smartTableData2 = smartTableData2;
    $scope.count = 0;
    $scope.openTransaction = function(txHash) {
        $scope.count++;
        console.log("txhash: " + txHash);
    };
    $scope.setParams = function(transaction){
      sharedProperties.setTransaction(transaction);
    }
    //editableOptions.theme = 'bs3';
    //editableThemes['bs3'].submitTpl = '<button type="submit" class="btn btn-primary btn-with-icon"><i class="ion-checkmark-round"></i></button>';
    //editableThemes['bs3'].cancelTpl = '<button type="button" ng-click="$form.$cancel()" class="btn btn-default btn-with-icon"><i class="ion-close-round"></i></button>';
  }

})();
