/**
 * @author v.lugovsky
 * created on 16.12.2015
 */
(function () {
    'use strict';
  
    angular.module('IotChainDashboard.pages.blocks-table')
        .controller('BlockDetailCtrl', BlockDetailCtrl);
  
  
    /** @ngInject */
    function BlockDetailCtrl($scope, $filter, $stateParams,editableOptions, editableThemes,sharedProperties) {
      $scope.block = sharedProperties.getBlock();
      console.log($scope.block.block_header.height);
      $scope.smartTablePageSize = 10;
      /*
      var sampleTransactions = [];
        for(var i=0;i<20;i++) {
        var tempBlockHash = "blockHash" + i;
        sampleTransactions.push({
            id: i,
            hash: tempBlockHash,
            age: '2s',
            data: 'test data',
            amount: "512"
          });
        }
        $scope.block = {
            numTransactions: sampleTransactions.length,
            blockHeight: 5000,
            difficulty: 2,
            blockSize: '10kb',
            version: "1",
            nonce: "2325342",
            reward: "2",
            timeStamp: '2AM',
            hash: "tempBlockHash",
            prevHash: "tempPrevBlockHash",
            nextHash: "tempNextBlockHash",
            transactions: sampleTransactions
            
          };*/
      //$scope.smartTableData2 = $filter('orderBy')($scope.smartTableData2, 'blockHeight', true);
  
  
      $scope.openBlockDetails = function(blockHash) {
          console.log("blockHash: " + blockHash);
      };
      $scope.setParams = function(block){
        sharedProperties.setBlock(block);
      }
    }
  
  })();
  