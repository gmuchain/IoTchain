/**
 * @author v.lugovsky
 * created on 16.12.2015
 */
(function () {
    'use strict';
  
    angular.module('IotChainDashboard.pages.blocks-table', ['ui.router'])
        .config(routeConfig)
  
    /** @ngInject */
    function routeConfig($stateProvider) {
      $stateProvider
          .state('blocks', {
            url: '/blocks-table',
            templateUrl: 'app/pages/blocks-table/blocks-table.html',
            title: 'Blocks',
            controller: 'BlocksTableCtrl',
            sidebarMeta: {
              icon: 'ion-cube',
              order: 0,
            }
          })
          .state('block_details',{
            url: '/blocks-table/{block_hash}',
            templateUrl: 'app/pages/widgets/details/block-detail/block-detail.html',
            title: 'Block Detail',
            controller: 'BlockDetailCtrl',
          });
    }
  
  })();
  