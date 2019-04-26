'use strict';

angular.module('IotChainDashboard', [
  'ngAnimate',
  'ui.bootstrap',
  'ui.sortable',
  'ui.router',
  'ngTouch',
  'toastr',
  'smart-table',
  "xeditable",
  'ui.slimscroll',
  'ngJsTree',
  'angular-progress-button-styles',
  'IotChainDashboard.theme',
  'IotChainDashboard.pages'
])
.controller('appCtrl', ['$scope', function($scope,sharedProperties) {
  $scope.startSearch = function(){
    console.log("test");
  };
  $scope.testBlocks = []
  $http.get('/assets/test.json').success(function (data){
    // $http.get('/assets/block_format.json').success(function (data){
       //$http.get('http://tree.star.is/public/block_format.json').success(function (data){
         var blocksPlaceholder = [];
         for(var i = 0; i < data.length; i++){
           var block = data[i];
           $scope.testBlocks.push(block);
           
         };
         sharedProperties.setTestBlocks($scope.testBlocks);
       });
}]).service('sharedProperties', function () {
  var block = 'First';
  var blocks = [];
  var transaction = 'init';
  var transactions = [];

  return {
      getBlock: function () {
          return block;
      },
      setBlock: function(value) {
          block = value;
      },
      getBlocks: function(){
        return blocks;
      },
      setBlocks: function(value){
        blocks = value;
      },
      getTransaction: function(){
        return transaction;
      },
      setTransaction: function(value){
        transaction = value;
      },
      
      getTransactions: function(){
        return transactions;
      },
      setTransactions: function(value){
        transactions = value;
      }
  };
});