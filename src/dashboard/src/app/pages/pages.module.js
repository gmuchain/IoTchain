/**
 * @author v.lugovsky
 * created on 16.12.2015
 */
(function () {
  'use strict';

  angular.module('IotChainDashboard.pages', [
    'ui.router',
    'IotChainDashboard.pages.dashboard',
    'IotChainDashboard.pages.blocks-table',
    'IotChainDashboard.pages.transactions-table',
  ])
      .config(routeConfig);

  /** @ngInject */
  function routeConfig($urlRouterProvider, baSidebarServiceProvider) {
    $urlRouterProvider.otherwise('/dashboard');
  }

})();
