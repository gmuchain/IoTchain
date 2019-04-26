/**
 * @author v.lugovsky
 * created on 16.12.2015
 */
(function () {
  'use strict';

  angular.module('IotChainDashboard.pages.blocks-table')
      .controller('BlocksTableCtrl', BlocksTableCtrl);


  /** @ngInject */
  function BlocksTableCtrl($scope, $filter,$http,$state,$stateParams,$timeout, editableOptions, editableThemes,sharedProperties) {    
    $scope.BlocksPageSize = 10;
    $scope.Blocks = [];
    
    $http.get('/assets/test.json').success(function (data){
     // $http.get('/assets/block_format.json').success(function (data){
        //$http.get('http://tree.star.is/public/block_format.json').success(function (data){
          var blocksPlaceholder = [];
          for(var i = 0; i < data.length; i++){
            var block = data[i];
            blocksPlaceholder.push(block);

          };
          $timeout(function() {
            $scope.Blocks = blocksPlaceholder;
            console.log("digest");         
            // anything you want can go here and will safely be run on the next digest.
            $scope.$apply();
            $scope.$digest();
            
            console.log($scope.Blocks.length);
          });
          
        });
        
  $scope.Blocks = $filter('orderBy')($scope.Blocks, 'block_header.height', true);

  $scope.setParams = function(block){
    sharedProperties.setBlock(block);
    /*
    var blocks = [];
    for(var i = 0; i < $scope.Blocks.length; i++){
      if($scope.Blocks[i].block_header.previous_hash == block.block_header.previous_hash){
        blocks.previous_block = $scope.Blocks[i];
      }
      if($scope.Blocks[i].block_header.next_hash == block.block_header.next_hash){
        blocks.next_block = $scope.Blocks[i];
      }
    }
    blocks.block = block;
    sharedProperties.setBlocks(blocks);
    */
  }
  }
})();
